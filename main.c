#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char DIR_PATH[] = "./exercises";
const int DIR_TYPE_CODE = 4;
const int FILE_TYPE_CODE = 8;
const int TOTAL_EXERCISES = 2;
const char README_FILE_NM[] = "README.md";

typedef struct {
    char *file_path;
    char *file_contents;
} File;

typedef struct {
    File *exercise_files;
    char *readme_contents;
    size_t file_ct;
} ExerciseDir;


/// This assumes that any path does not contain any dividers
/// *base_path = "../" or "./" or "/" if needed, otherwise pass ""
char* build_file_path(char **paths, int size, char *base_path) {
    int str_len = 1;
    for (int i = 0; i < size; i++) {
        str_len += strlen(paths[i]) + 1;
    }

    char *str_buff = malloc(str_len);
    if (str_buff == NULL) {
        printf("concat_path_dyn malloc failed");
        exit(1);
    }

    // initialize the buffer to an empty string
    strcpy(str_buff, "");

    for (int i = 0; i < size; i++) {
        if (strlen(str_buff) == 0) {
            sprintf(str_buff, "%s%s", base_path, paths[i]);
        } else {
            sprintf(str_buff, "%s/%s", str_buff, paths[i]);
        }
    }

    return str_buff;
}


char* read_file_contents(char *file_path) {
    struct stat fstat_buff;
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        printf("Failed to open file \n");
        exit(1);
    }

    if (fstat(fileno(file), &fstat_buff) == -1) {
        printf("Failed to get file stats \n");
        fclose(file);
        exit(1);

    }
    long file_size = fstat_buff.st_size;
    char *file_buff = malloc(file_size + 1);

    if (file_buff == NULL) {
        printf("Failed to allocate memory for reading file \n");
        fclose(file);
        exit(1);
    }

    fread(file_buff, 1, file_size, file);
    file_buff[file_size] = '\0';
    fclose(file);

    return file_buff;
}

void add_exercise(ExerciseDir **exercise, File *files, int file_ct, char *readme, int index) {
    (*exercise)[index].exercise_files = malloc(sizeof(File) * file_ct);

    for (int i = 0; i < file_ct; i++) {
        (*exercise)[index].exercise_files[i].file_path = strdup(files[i].file_path);
        (*exercise)[index].exercise_files[i].file_contents = strdup(files[i].file_contents);
    }

    (*exercise)[index].file_ct = file_ct;
    (*exercise)[index].readme_contents = strdup(readme);
}

void load_exercises(ExerciseDir **exercise) {
    struct dirent *de;
    DIR *dir = opendir(DIR_PATH);

    if (dir == NULL) {
        printf("Could not open directory \n");
        exit(1);
    }

    int exercise_ct = 0;

    while ((de = readdir(dir)) != NULL) {
        int file_type = de->d_type;

        if (file_type != DIR_TYPE_CODE) continue;
        if (strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".") == 0) continue;

        printf("dir: %s \n", de->d_name);

        // expecting only directories here at 1 layer depth, not using recursion cause lazy
        char *paths[] = { (char *)DIR_PATH, de->d_name };
        char *nested_path = build_file_path(paths, 2, "");

        struct dirent *nde;
        DIR *ndir = opendir(nested_path);

        if (ndir == NULL) {
            printf("Could not open nested directory \n");
            exit(1);
        }

        int file_ct = 0;
        File *exercise_files;
        char *readme_contents;

        while ((nde = readdir(ndir)) != NULL) {
            int file_type = nde->d_type;
            char *file_name = nde->d_name;
            if (file_type == FILE_TYPE_CODE) {
                char *paths[] = { (char *)DIR_PATH, de->d_name, nde->d_name};
                char *full_path = build_file_path(paths, 3, "");
                printf("Processing: %s \n", full_path); 

                char *file_contents = read_file_contents(full_path);
                int file_path_size = strlen(full_path) + 1;
                int file_contents_size = strlen(file_contents) + 1;

                if (strcmp(file_name, README_FILE_NM) == 0) {
                    readme_contents = malloc(file_contents_size);
                    strcpy(readme_contents, file_contents);
                } else { // these can be assumed to be exercise files
                    if (file_ct == 0) {
                        exercise_files = malloc(sizeof(File));
                    } else {
                        exercise_files = realloc(exercise_files, (file_ct + 1) * sizeof(File));
                    }         

                    exercise_files[file_ct].file_path = malloc(file_path_size);
                    strcpy(exercise_files[file_ct].file_path, full_path);
                    exercise_files[file_ct].file_contents = malloc(file_contents_size);
                    strcpy(exercise_files[file_ct].file_contents, file_contents);

                    file_ct++;
                }

                free(full_path);
                free(file_contents);
            }
        }

        add_exercise(exercise, exercise_files, file_ct, readme_contents, exercise_ct);
        exercise_ct++;
        closedir(ndir);
        free(nested_path);
    }

    closedir(dir);
}

int main() {
    ExerciseDir *exercises = malloc(TOTAL_EXERCISES * sizeof(ExerciseDir));

    if (exercises == NULL) {
        perror("Failed allocate memory for exercise");
        exit(1);
    }

    load_exercises(&exercises);

    for (int i = 0; i < TOTAL_EXERCISES; i++) {
        printf("File: %i | readme: %s \n", i, exercises[i].readme_contents); 

        for (int e = 0; e < exercises[i].file_ct; e++) {
            printf("File path: %s \n", exercises[i].exercise_files[e].file_path); 
            printf("exercise contents: %s \n", exercises[i].exercise_files[e].file_contents);
            
        }
    }

    // cleanup 
    for (int i = 0; i < TOTAL_EXERCISES; i++) {
        for (int e = 0; e < exercises[i].file_ct; e++) {
            free(exercises[i].exercise_files[e].file_path);
            free(exercises[i].exercise_files[e].file_contents);
        }
        free(exercises[i].readme_contents);
    }

    free(exercises);

    return 0;
}
