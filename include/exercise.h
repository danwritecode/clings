#ifndef EXERCISE_H
#define EXERCISE_H

#include "files.h"


typedef struct {
    char* readme;
    FileCollection* exercise_files;
} Exercise;

Exercise *create_exercise(FileCollection *files);
char* get_readme(FileCollection *dir);
FileCollection* get_exercises(FileCollection *dir);

#endif
