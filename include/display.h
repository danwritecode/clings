#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include "execution_state.h"
#include "exercise.h"


typedef enum {
    FAILURE,
    MARKED_INCOMPLETE,
    COMPLETE,
} DisplayMode;

void display(Exercise *exercise, ExecutionState *state, DisplayMode display_mode);
void display_debug(Exercise *exercise);
void display_failure(Exercise *exercise, ExecutionState *state);
void display_success();
void display_marked_incomplete(Exercise *exercise, ExecutionState *state);
void display_progress(int current_exercise, int total_exercises);

#endif

