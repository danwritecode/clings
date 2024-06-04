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

typedef struct {
  FailureMode failure_mode;
  bool marked_incomplete;
  int failing_file;
} Failure;

void display_debug(Exercise *exercise);
void display_failure(Exercise *exercise, Failure *failure);
void display_success();
void display_marked_incomplete(Exercise *exercise, Failure *failure);
void get_failing_exercise(Exercise *exercise, Failure *failure);
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
  Failure failure;
  failure.failure_mode = NONE;
  failure.failing_file = -1;

  while (keep_running) {
    delay(1);
    load_files(dirs);

    for (int d = 0; d < TOTAL_EXERCISES_DIRS; d++) {
      Exercise exercise = create_exercise(dirs[d]);
      bool file_diff = is_file_diff(&exercise);

      if (DEBUG_MODE == true) {
        display_debug(&exercise);
        continue;
      }

      if (rerun_all == true) {
        get_failing_exercise(&exercise, &failure);
        if (failure.failure_mode != NONE) {
          display_failure(&exercise, &failure);
          rerun_all = false;
          break;
        }

        if (failure.failure_mode == NONE && failure.marked_incomplete == true) {
          display_marked_incomplete(&exercise, &failure);
          rerun_all = false;
          break;
        }

        // end of exercises, no failures
        if (d == TOTAL_EXERCISES_DIRS - 1) {
          display_success();
          rerun_all = false;
        }
      }

      if (file_diff == true) {
        get_failing_exercise(&exercise, &failure);
        if (failure.failure_mode != NONE) {
          display_failure(&exercise, &failure);
          rerun_all = false;
          break;
        }

        if (failure.failure_mode == NONE && failure.marked_incomplete == true) {
          display_marked_incomplete(&exercise, &failure);
          rerun_all = false;
          break;
        }

        if (failure.failure_mode == NONE && failure.marked_incomplete == false) {
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


void get_failing_exercise(Exercise *exercise, Failure *failure) {
  int file_ct = exercise->exercise_files->file_ct;
  File *files = exercise->exercise_files->files;

  for (int e = 0; e < file_ct; e++) {
    File file = files[e];
    char *file_name_no_ext = file.file_name_no_ext;
    char *file_path = file.file_path;

    FailureMode failure_mode = find_failure_mode(file_path, file_name_no_ext);
    failure->failure_mode = failure_mode;
    failure->marked_incomplete = file.marked_incomplete;
    failure->failing_file = e;

    if (failure_mode != NONE || file.marked_incomplete == true) {
      return;
    }
  }

  failure->failure_mode = NONE;
  failure->marked_incomplete = false;
  failure->failing_file = -1;
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

void display_success() {
  char *msg = "      _ _                 \n"
              "     | (_)                \n"
              "  ___| |_ _ __   __ _ ___ \n"
              " / __| | | '_ \\ / _` / __|\n"
              "| (__| | | | | | (_| \\__ \\\n"
              " \\___|_|_|_| |_|\\__, |___/\n"
              "                 __/ |    \n"
              "                |___/     \n";

  exec_cmd("clear");
  printf("%s\n", msg);
  puts("\n");
  puts("Congratulations on completing clings!");
}

void display_marked_incomplete(Exercise *exercise, Failure *failure) {
  char *msg = "1 | // ❌ I AM NOT DONE \n"
              "2 | \n"
              "3 | \n";

  exec_cmd("clear");
  printf("✅ You've completed exercise: %s \n", exercise->exercise_files->files[failure->failing_file].file_path);
  puts("");
  puts("You can keep working on it for fun, or delete the commented line below in the exercise file to proceed to the next exercise. \n");
  printf("%s\n", msg);
}

void display_debug(Exercise *exercise) {
  File exercise_file = exercise->exercise_files->files[0];
  printf("Exercise: %s | File type: %i | marked incomplete: %i | file diff "
         "found: %i \n",
         exercise_file.file_name, exercise_file.file_type,
         exercise_file.marked_incomplete, exercise_file.file_diff);
}
