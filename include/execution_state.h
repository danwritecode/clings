#ifndef EXECUTION_STATE_H
#define EXECUTION_STATE_H

#include <stdbool.h>

typedef enum {
    RUNTIME,
    COMPILATION,
    NONE,
} FailureMode;

typedef struct {
    FailureMode failure_mode;
    bool marked_incomplete;
    int failing_file;
    int total_files;
} ExecutionState;

#endif

