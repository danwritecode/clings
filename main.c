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

typedef struct {
    char *file_path;
    char *file_contents;
} File;

typedef struct {
    File **exercise_files;
    char *readme_contents;
} ExerciseDir;


/// This assumes that any path does not contain any dividers
/// *base_path = "../" or "./" or "/" if needed, otherwise pass ""
char* concat_path_dyn(char **paths, int size, char *base_path) {
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

void read_file(char *file_path) {
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

    printf("file contents: %s \n", file_buff);

    fclose(file);
    free(file_buff);
}


void load_exercises(ExerciseDir *exercise) {
    struct dirent *de;
    DIR *dir = opendir(DIR_PATH);

    if (dir == NULL) {
        printf("Could not open directory \n");
        exit(1);
    }

    while ((de = readdir(dir)) != NULL) {
        int file_type = de->d_type;

        if (file_type != DIR_TYPE_CODE) continue;
        if (strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".") == 0) continue;

        // expecting only directories here at 1 layer depth, not using recursion cause lazy
        char *paths[] = { (char *)DIR_PATH, de->d_name };
        char *nested_path = concat_path_dyn(paths, 2, "");

        struct dirent *nde;
        DIR *ndir = opendir(nested_path);

        if (ndir == NULL) {
            printf("Could not open nested directory \n");
            exit(1);
        }

        while ((nde = readdir(ndir)) != NULL) {
            int file_type = nde->d_type;
            if (file_type == FILE_TYPE_CODE) {
                char *paths[] = { (char *)DIR_PATH, de->d_name, nde->d_name};
                char *full_path = concat_path_dyn(paths, 3, "");
                printf("Processing: %s \n", full_path); 
                read_file(full_path);

                free(full_path);
            }
        }

        closedir(ndir);
        free(nested_path);
    }

    closedir(dir);
}

int main() {
    ExerciseDir exercise;
    load_exercises(&exercise);

    return 0;
}

// FILE *file = fopen("prog.c", "r");
// if (file == NULL) {
//     perror("Failed to open file");
//     return 1;
// }
// fputs(prog, file);
// fclose(file);
//
// // compile the program
// if (system("gcc -o prog prog.c") == -1) {
//     perror("Failed to compile program");
//     return 1;
// }
//
// // run the program
// if (system("./prog") == -1) {
//     perror("Failed to run program");
//     return 1;
// }
