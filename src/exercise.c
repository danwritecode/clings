#include "exercise.h"
#include "files.h"
#include <stdlib.h>


Exercise *create_exercise(FileCollection *dirs) {
    Exercise *exercise = malloc(sizeof(Exercise));

    exercise->readme = get_readme(dirs);
    exercise->exercise_files = get_exercises(dirs);

    return exercise;
}

char* get_readme(FileCollection *dir) {
    for (size_t f = 0; f < dir->file_ct; f++) {
        FileType file_type = dir->files[f].file_type;
        if (file_type == README) {
            return dir->files[f].file_contents;
        }
    }
    puts("error: no readme found in directory");
    exit(1);
}

FileCollection* get_exercises(FileCollection *dir) {
    FileCollection* result = malloc(sizeof(FileCollection));
    if (result == NULL) {
        perror("Failed to allocate memory for result");
        exit(1);
    }

    result->files = NULL;
    result->file_ct = 0;

    for (size_t f = 0; f < dir->file_ct; f++) {
        FileType file_type = dir->files[f].file_type;
        if (file_type == EXERCISE) {
            result->files = realloc(result->files, (result->file_ct + 1) * sizeof(File));
            if (result->files == NULL) {
                perror("Failed to realloc memory for get_exercises");
                exit(1);
            }

            result->files[result->file_ct] = dir->files[f];
            result->file_ct++;
        }
    }

    return result;
}
