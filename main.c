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

static volatile sig_atomic_t keep_running = 1;
static void sig_handler(int _)
{
    (void)_;
    keep_running = 0;
}


int main() {
    signal(SIGINT, sig_handler);

    Directory **dirs = malloc(TOTAL_EXERCISES_DIRS * sizeof(Directory));
    if (dirs == NULL) {
        perror("Failed allocate memory for dirs");
        exit(1);
    }

    for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
        dirs[i] = NULL;
    }

    while(keep_running) {
        delay(1);
        load_files(dirs);
        for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
            for (size_t e = 0; e < dirs[i]->file_ct; e++) {
                // look for file diffs
                bool file_diff = dirs[i]->files[e].file_diff;
                char *file_path = dirs[i]->files[e].file_path;
                char *file_name_no_ext = dirs[i]->files[e].file_name_no_ext;
                FileType file_type = dirs[i]->files[e].file_type;

                if (file_type == EXERCISE) {
                    int compile_res = exec_compile(file_path, file_name_no_ext);
                    printf("compile exec exit code: %i \n", compile_res);
                    int run_res = exec_run(file_name_no_ext);
                    printf("run exec exit code: %i \n", run_res);
                }

                if (file_diff == true) {
                    printf("file diff for: %s \n", file_path);
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
