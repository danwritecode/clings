#include "display.h"
#include "execution_state.h"
#include "exercise.h"
#include "files.h"
#include "runna.h"
#include "utils.h"

#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int TOTAL_EXERCISES_DIRS = 3; // TODO: Make this dynamic in the future
static volatile sig_atomic_t keep_running = 1;

void exec_exercise(Exercise *exercise, ExecutionState *state);
FailureMode find_failure_mode(char *file_path, char *file_name_no_ext);
bool is_file_diff(Exercise *exercise);

static void sig_handler(int _);
void print_usage();
int count_dir(char *dir);

int main(int argc, char *argv[]) {
    signal(SIGINT, sig_handler);

    TOTAL_EXERCISES_DIRS = count_dir("./exercises");
    if (TOTAL_EXERCISES_DIRS == -1) {
        return 1;
    }

    int start_at = 1;
    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "s:")) != -1) {
        switch (c) {
        case 's':
            start_at = atoi(optarg);

            if (start_at > TOTAL_EXERCISES_DIRS || start_at < 1) {
                printf("error: cannot start at %d (max. exercises: %d)\n",
                       start_at, TOTAL_EXERCISES_DIRS);
                return EXIT_FAILURE;
            }
            printf("Starting at exercise %d ...\n", start_at);

            delay(2);
            break;
        default:
            print_usage();
            return EXIT_SUCCESS;
        }
    }

    int rerun_all = true;
    ExecutionState exercise_state;
    exercise_state.failure_mode = NONE;
    exercise_state.failing_file = -1;
    exercise_state.total_files = -1;

    FileCollection **dirs =
        malloc(TOTAL_EXERCISES_DIRS * sizeof(FileCollection *));
    if (dirs == NULL) {
        perror("Failed allocate memory for dirs");
        exit(1);
    }

    for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
        dirs[i] = NULL;
    }

    while (keep_running) {
        delay(1);

        int exercise_file_ct = load_files(dirs);
        exercise_state.total_files = exercise_file_ct;

        for (int d = (start_at - 1); d < TOTAL_EXERCISES_DIRS; d++) {
            Exercise *exercise = create_exercise(dirs[d]);
            bool file_diff = is_file_diff(exercise);

#ifdef DEBUG
            display_debug(&exercise);
            continue;
#endif

            if (rerun_all == true) {
                exec_exercise(exercise, &exercise_state);

                if (exercise_state.failure_mode != NONE) {
                    display(exercise, &exercise_state, FAILURE);
                    rerun_all = false;
                    goto clean_exercise;
                }

                if (exercise_state.failure_mode == NONE &&
                    exercise_state.marked_incomplete == true) {
                    display(exercise, &exercise_state, MARKED_INCOMPLETE);
                    rerun_all = false;
                    goto clean_exercise;
                }

                // end of exercises, no failures
                if (d == TOTAL_EXERCISES_DIRS - 1) {
                    display(exercise, &exercise_state, COMPLETE);
                    rerun_all = false;
                }
            }

            if (file_diff == true) {
                exec_exercise(exercise, &exercise_state);

                if (exercise_state.failure_mode != NONE) {
                    display(exercise, &exercise_state, FAILURE);
                    rerun_all = false;
                    goto clean_exercise;
                }

                if (exercise_state.failure_mode == NONE &&
                    exercise_state.marked_incomplete == true) {
                    display(exercise, &exercise_state, MARKED_INCOMPLETE);
                    rerun_all = false;
                    goto clean_exercise;
                }

                if (exercise_state.failure_mode == NONE &&
                    exercise_state.marked_incomplete == false) {
                    rerun_all = true;
                }
            }

        clean_exercise:
            free(exercise->exercise_files->files);
            free(exercise->exercise_files);
            free(exercise);
            }
        }

    for (int di = 0; di < TOTAL_EXERCISES_DIRS; di++) {
        if (dirs[di]) {
            for (size_t e = 0; e < dirs[di]->file_ct; e++) {
                free(dirs[di]->files[e].file_path);
                free(dirs[di]->files[e].file_name);
                free(dirs[di]->files[e].file_name_no_ext);
                free(dirs[di]->files[e].parent_dir_path);
                free(dirs[di]->files[e].file_contents);
            }
            free(dirs[di]->files);
            free(dirs[di]);
        }
    }

    free(dirs);
          
    return 0;
}

void exec_exercise(Exercise *exercise, ExecutionState *exercise_state) {
    int file_ct = exercise->exercise_files->file_ct;
    File *files = exercise->exercise_files->files;

    for (int e = 0; e < file_ct; e++) {
        File file = files[e];
        char *file_name_no_ext = file.file_name_no_ext;
        char *file_path = file.file_path;

        FailureMode failure_mode =
            find_failure_mode(file_path, file_name_no_ext);
        exercise_state->failure_mode = failure_mode;
        exercise_state->marked_incomplete = file.marked_incomplete;
        exercise_state->failing_file = e;

        if (failure_mode != NONE || file.marked_incomplete == true) {
            return;
        }
    }

    exercise_state->failure_mode = NONE;
    exercise_state->marked_incomplete = false;
    exercise_state->failing_file = -1;
}

FailureMode find_failure_mode(char *file_path, char *file_name_no_ext) {
    int comp_res = exec_compile(file_path, file_name_no_ext);
    if (comp_res != 0) {
        return COMPILATION;
    }

    int run_res = exec_run(file_name_no_ext);
    if (run_res != 0) {
        return RUNTIME;
    }

    return NONE;
}

bool is_file_diff(Exercise *exercise) {
    int file_ct = exercise->exercise_files->file_ct;
    File *files = exercise->exercise_files->files;
    bool is_file_diff = false;

    for (int e = 0; e < file_ct; e++) {
        File file = files[e];
        bool file_diff = file.file_diff;
        if (file_diff == true) {
            is_file_diff = true;
            break;
        }
    }

    return is_file_diff;
}

static void sig_handler(int _) {
    (void)_;
    keep_running = 0;
}

int count_dir(char *dir) {
    struct dirent *dp;
    DIR *fd;

    int dir_count = 0;

    if ((fd = opendir(dir)) == NULL) {
        fprintf(stderr, "count_dir: can't open %s\n", dir);
        return -1;
    }
    while ((dp = readdir(fd)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue; /* skip self and parent */
        dir_count++;
    }
    closedir(fd);

    return dir_count;
}

void print_usage() {
    printf("Usage:\n\n"
           "-s N\tStart at exercise N (between 1 and %d)"
           "\n",
           TOTAL_EXERCISES_DIRS);
}
