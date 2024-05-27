#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "files.h"
#include "utils.h"
#include "runna.h"

const int TOTAL_EXERCISES_DIRS = 2; // TODO: Make this dynamic in the future

typedef enum {
    RUNTIME,
    COMPILATION,
    NONE,
} FailureMode;

static volatile sig_atomic_t keep_running = 1;
static void sig_handler(int _)
{
    (void)_;
    keep_running = 0;
}

File* get_readme(FileCollection *dir) {
    for (size_t f = 0; f < dir->file_ct; f++) {
        FileType file_type = dir->files[f].file_type;
        if (file_type == README) {
            return &dir->files[f];
        }
    }
    puts("error: no readme found in directory");
    exit(1);
}

FileCollection get_exercises(FileCollection *dir) {
    FileCollection result;
    result.files = NULL;
    result.file_ct = 0;

    for (size_t f = 0; f < dir->file_ct; f++) {
        FileType file_type = dir->files[f].file_type;
        if (file_type == EXERCISE) {
            result.files = realloc(result.files, (result.file_ct + 1) * sizeof(File));
            if (result.files == NULL) {
                perror("Failed to realloc memory for get_exercises");
                exit(1);
            }

            result.files[result.file_ct] = dir->files[f];
            result.file_ct++;
        }
    }

    return result;
}

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

    int index = 0;
    int failing_exercise = 0;
    char *failing_file_name = NULL;
    char *failing_file_path = NULL;
    FailureMode cur_exercie_failure_mode = NONE;
    bool file_diff_detected = false;
    bool reprint_required = true; // default to true

    while(keep_running) {
        delay(1);
        load_files(dirs);
        for (int e = 0; e < TOTAL_EXERCISES_DIRS; e++) {
            FileCollection exercises = get_exercises(dirs[e]);

            for (size_t f = 0; f < exercises.file_ct; f++) {
                // look for file diffs
                bool file_diff = exercises.files[f].file_diff;
                char *file_path = exercises.files[f].file_path;
                char *file_name_no_ext = exercises.files[f].file_name_no_ext;

                // on first index or file_diff we want to try to compile everything to find where we're at in the exercises
                if (index == 0 || file_diff_detected == true) {
                    // attempt both compile and runtime to find errors
                    int compile_res = exec_compile(file_path, file_name_no_ext);
                    if (compile_res != 0) {
                        cur_exercie_failure_mode = COMPILATION;
                        failing_exercise = e;
                        failing_file_name = file_name_no_ext;
                        failing_file_path = file_path;
                        break;
                    }

                    int run_res = exec_run(file_name_no_ext);
                    if (run_res != 0) {
                        cur_exercie_failure_mode = RUNTIME;
                        failing_exercise = e;
                        failing_file_name = file_name_no_ext;
                        failing_file_path = file_path;
                        break;
                    }
                }

                // don't care about file diffs on first iteration
                if (file_diff == true && index != 0) {
                    file_diff_detected = true;
                    reprint_required = true;
                } else {
                    file_diff_detected = false;
                }
            }
        }


        if (reprint_required == true) {
            File *readme = get_readme(dirs[failing_exercise]);
            exec_cmd("clear");

            // print readme
            printf("%s \n\n", readme->file_contents);

            // render current exercise
            if (cur_exercie_failure_mode == COMPILATION) {
                exec_compile_output(failing_file_path, failing_file_name);
            }

            if (cur_exercie_failure_mode == RUNTIME) {
                exec_run_output(failing_file_name);
            }

            reprint_required = false;
        }

        index++;
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
