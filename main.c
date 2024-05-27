#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "exercise.h"
#include "files.h"
#include "utils.h"
#include "runna.h"

const int TOTAL_EXERCISES_DIRS = 2; // TODO: Make this dynamic in the future

typedef enum {
    RUNTIME,
    COMPILATION,
    NONE,
} FailureMode;

typedef struct {
    FailureMode failure_mode;
    int failing_file;
} Failure;

static volatile sig_atomic_t keep_running = 1;
static void sig_handler(int _)
{
    (void)_;
    keep_running = 0;
}

void display_failure(Exercise *exercise, Failure *failure);
void display_success();
// returns 0 for no failure, 1 for failure
void get_failing_exercise(Exercise *exercise, Failure *failure);
bool is_file_diff(Exercise *exercise);

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
    Failure failure;
    failure.failure_mode = NONE;
    failure.failing_file = -1;

    while(keep_running) {
        delay(1);
        load_files(dirs);

        for (int d = 0; d < TOTAL_EXERCISES_DIRS; d++) {
            Exercise exercise = create_exercise(dirs[d]);
            bool file_diff = is_file_diff(&exercise);

            if (rerun_all == true) {
                get_failing_exercise(&exercise, &failure);
                if (failure.failure_mode != 2) {
                    display_failure(&exercise, &failure);
                    rerun_all = false;
                    break;
                }

                // end of exercises, no failures
                if (d == TOTAL_EXERCISES_DIRS -1) {
                    exec_cmd("clear");
                    display_success();
                    rerun_all = false;
                }
            }

            if (file_diff == true) {
                get_failing_exercise(&exercise, &failure);
                if (failure.failure_mode != 2) {
                    display_failure(&exercise, &failure);
                    rerun_all = false;
                    break;
                } else {
                    rerun_all = true; // no issues found with file diff, need to now find next failing exercise
                }
            }
        }
    }

    puts("stopped by ctrl+c");

    // cleanup 
    for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
        for (size_t e = 0; e < dirs[i]->file_ct; e++) {
            free(dirs[i]->files[e].file_path);
            free(dirs[i]->files[e].file_contents);
        }
    }

    free(dirs);
    return 0;
}

void display_failure(Exercise *exercise, Failure *failure) {
    FailureMode failure_type = failure->failure_mode;
    File failed_file = exercise->exercise_files->files[failure->failing_file];

    exec_cmd("clear");
    printf("%s \n\n", exercise->readme);

    if (failure_type == COMPILATION) {
        exec_compile_output(failed_file.file_path, failed_file.file_name_no_ext);
        return;
    }

    if (failure_type == RUNTIME) {
        exec_run_output(failed_file.file_name_no_ext);
        return;
    }
}

void get_failing_exercise(Exercise *exercise, Failure *failure) {
    int file_ct = exercise->exercise_files->file_ct;
    File *files = exercise->exercise_files->files;

    for (int e = 0; e < file_ct; e++) {
        File file = files[e]; 
        char *file_name_no_ext = file.file_name_no_ext;
        char *file_path = file.file_path;

        int comp_res = exec_compile(file_path, file_name_no_ext);
        if (comp_res != 0) {
            puts("Failed to compile");
            failure->failure_mode = COMPILATION;
            failure->failing_file = e;
            return;
        }

        int run_res = exec_run(file_name_no_ext);
        if (run_res != 0) {
            puts("Failed to run");
            failure->failure_mode = RUNTIME;
            failure->failing_file = e;
            return;
        }
    }

    failure->failure_mode = NONE;
    failure->failing_file = -1;
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

void display_success() {
    char *msg = 
        "      _ _                 \n"
        "     | (_)                \n"
        "  ___| |_ _ __   __ _ ___ \n"
        " / __| | | '_ \\ / _` / __|\n"
        "| (__| | | | | | (_| \\__ \\\n"
        " \\___|_|_|_| |_|\\__, |___/\n"
        "                 __/ |    \n"
        "                |___/     \n";
    
    printf("%s\n", msg);
    puts("\n");
    puts("Congratulations on completing clings!");
}
