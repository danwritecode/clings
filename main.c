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

const bool DEBUG_MODE = false;
const int TOTAL_EXERCISES_DIRS = 2; // TODO: Make this dynamic in the future
static volatile sig_atomic_t keep_running = 1;

typedef enum {
    RUNTIME,
    COMPILATION,
    NONE,
} FailureMode;

typedef enum {
    FAILURE,
    MARKED_INCOMPLETE,
    COMPLETE,
} DisplayMode;

typedef struct {
    FailureMode failure_mode;
    bool marked_incomplete;
    int failing_file;
    int total_files;
} ExecutionState;

void display(Exercise *exercise, ExecutionState *state, DisplayMode display_mode);
void display_debug(Exercise *exercise);
void display_failure(Exercise *exercise, ExecutionState *state);
void display_success();
void display_marked_incomplete(Exercise *exercise, ExecutionState *state);
void display_progress(int current_exercise, int total_exercises);
void exec_exercise(Exercise *exercise, ExecutionState *state);
FailureMode find_failure_mode(char *file_path, char *file_name_no_ext);
bool is_file_diff(Exercise *exercise);
static void sig_handler(int _);

int main() {
    signal(SIGINT, sig_handler);

    FileCollection **dirs = malloc(TOTAL_EXERCISES_DIRS * sizeof(FileCollection));
    if (dirs == NULL) {
        perror("Failed allocate memory for dirs");
        exit(1);
    }

    for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
        dirs[i] = NULL;
    }

    int rerun_all = true;
    ExecutionState exercise_state;
    exercise_state.failure_mode = NONE;
    exercise_state.failing_file = -1;
    exercise_state.total_files = -1;

    while (keep_running) {
        delay(1);

        int exercise_file_ct = load_files(dirs);
        exercise_state.total_files = exercise_file_ct;

        for (int d = 0; d < TOTAL_EXERCISES_DIRS; d++) {
            Exercise exercise = create_exercise(dirs[d]);
            bool file_diff = is_file_diff(&exercise);

            if (DEBUG_MODE == true) {
                display_debug(&exercise);
                continue;
            }

            if (rerun_all == true) {
                exec_exercise(&exercise, &exercise_state);

                if (exercise_state.failure_mode != NONE) {
                    display(&exercise, &exercise_state, FAILURE);
                    rerun_all = false;
                    break;
                }

                if (exercise_state.failure_mode == NONE && exercise_state.marked_incomplete == true) {
                    display(&exercise, &exercise_state, MARKED_INCOMPLETE);
                    rerun_all = false;
                    break;
                }

                // end of exercises, no failures
                if (d == TOTAL_EXERCISES_DIRS - 1) {
                    display(&exercise, &exercise_state, COMPLETE);
                    rerun_all = false;
                }
            }

            if (file_diff == true) {
                exec_exercise(&exercise, &exercise_state);

                if (exercise_state.failure_mode != NONE) {
                    display(&exercise, &exercise_state, FAILURE);
                    rerun_all = false;
                    break;
                }

                if (exercise_state.failure_mode == NONE && exercise_state.marked_incomplete == true) {
                    display(&exercise, &exercise_state, MARKED_INCOMPLETE);
                    rerun_all = false;
                    break;
                }

                if (exercise_state.failure_mode == NONE && exercise_state.marked_incomplete == false) {
                    rerun_all = true;
                }
            }
        }
    }

    for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
        for (size_t e = 0; e < dirs[i]->file_ct; e++) {
            free(dirs[i]->files[e].file_path);
            free(dirs[i]->files[e].file_contents);
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

        FailureMode failure_mode = find_failure_mode(file_path, file_name_no_ext);
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

void display(
    Exercise *exercise, 
    ExecutionState *exercise_state, 
    DisplayMode display_mode
) {
    switch (display_mode) {
        case FAILURE:
            exec_cmd("clear");
            display_progress(exercise_state->failing_file, exercise_state->total_files);
            puts("");

            display_failure(exercise, exercise_state);
            break;
        case MARKED_INCOMPLETE:
            exec_cmd("clear");
            display_progress(exercise_state->failing_file, exercise_state->total_files);
            puts("");

            display_marked_incomplete(exercise, exercise_state);
            break;
        case COMPLETE:
            display_success();
            break;
    }
}

void display_failure(Exercise *exercise, ExecutionState *exercise_state) {
    FailureMode failure_type = exercise_state->failure_mode;
    File failed_file = exercise->exercise_files->files[exercise_state->failing_file];

    if (failure_type == COMPILATION) {
        printf("⚠️ \033[1;31mCompiling of %s failed! Please try again. Here's the output: \033[0m\n\n", exercise->exercise_files->files[exercise_state->failing_file].file_path);
        exec_compile_output(failed_file.file_path, failed_file.file_name_no_ext);
        return;
    }

    if (failure_type == RUNTIME) {
        printf("⚠️  \033[1;31mRunning of %s failed! Please try again. Here's the output: \033[0m\n\n", exercise->exercise_files->files[exercise_state->failing_file].file_path);
        exec_run_output(failed_file.file_name_no_ext);
        return;
    }
}

void display_marked_incomplete(Exercise *exercise, ExecutionState *exercise_state) {
    File failed_file = exercise->exercise_files->files[exercise_state->failing_file];

    char msg[] = "\033[1;34m1 | \033[0m// ❌ I AM NOT DONE \n"
                 "\033[1;34m2 | \033[0m\n"
                 "\033[1;34m3 | \033[0m\n";

    printf("✅ \033[1;32mYou've completed exercise: %s \033[0m\n", exercise->exercise_files->files[exercise_state->failing_file].file_path);
    puts("");
    printf("😎 The code is compiling! 😎 \n");
    puts("");
    printf("Output: \n");
    puts("==========================================");
    exec_run_output(failed_file.file_name_no_ext);
    puts("==========================================");
    puts("");
    puts("You can keep working on it for fun,\nor delete the commented line below in the exercise file to proceed to the next exercise. \n");
    printf("%s\n", msg);
}

void display_progress(int current_exercise, int total_exercises) {
    int current_exercise_non_zero = current_exercise == 0 ? 1:current_exercise;
    float progress = (float)current_exercise_non_zero / total_exercises;
    char msg[300] = "";

    for (int ci = 0; ci < 50; ci++) {
        float cip = (float)ci / 50;
        if (cip * 100 <= progress * 100) {
            strcat(msg, "█");
        } else {
            strcat(msg, "-");
        }
    }

    printf("Progress: \033[1;32m%s |\033[0m\n", msg);
}

void display_success() {
    char msg[] = "\033[1;32m"
                 "      _ _                 \n"
                 "     | (_)                \n"
                 "  ___| |_ _ __   __ _ ___ \n"
                 " / __| | | '_ \\ / _` / __|\n"
                 "| (__| | | | | | (_| \\__ \\\n"
                 " \\___|_|_|_| |_|\\__, |___/\n"
                 "                 __/ |    \n"
                 "                |___/     \n"
                 "\033[0m";

    exec_cmd("clear");
    printf("%s\n", msg);
    printf("\033[1;32mCongratulations on completing clings!\033[0m\n");
}

void display_debug(Exercise *exercise) {
    for (size_t fi = 0; fi < exercise->exercise_files->file_ct; fi++) {
        File exercise_file = exercise->exercise_files->files[fi];

        printf("Exercise: %s | File type: %i | marked incomplete: %i | file diff "
             "found: %i \n",
             exercise_file.file_name, exercise_file.file_type,
             exercise_file.marked_incomplete, exercise_file.file_diff);
    }
}
