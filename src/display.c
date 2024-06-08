#include "display.h"
#include "runna.h"
#include <stdio.h>
#include <string.h>

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
