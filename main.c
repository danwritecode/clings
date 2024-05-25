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
const int TOTAL_EXERCISES_DIRS = 2;
const char README_FILE_NM[] = "README.md";

typedef enum {
    EXERCISE,
    README
} FileType;

typedef struct {
    char *file_path;
    char *file_contents;
    FileType file_type;
} File;

typedef struct {
    File *files;
    size_t file_ct;
} Directory;


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

void add_dir(Directory **dirs, File *files, int file_ct, int dir_idx) {
    (*dirs)[dir_idx].files = malloc(sizeof(File) * file_ct);

    for (int i = 0; i < file_ct; i++) {
        (*dirs)[dir_idx].files[i].file_path = strdup(files[i].file_path);
        (*dirs)[dir_idx].files[i].file_contents = strdup(files[i].file_contents);
        (*dirs)[dir_idx].files[i].file_type = files[i].file_type;
    }

    (*dirs)[dir_idx].file_ct = file_ct;
}

/// Loops through target directory path and loads files into Directory double pointer
void load_files(Directory **dirs) {
    struct dirent *de;
    DIR *dir = opendir(DIR_PATH);

    if (dir == NULL) {
        printf("Could not open directory \n");
        exit(1);
    }

    File *files;
    int dir_idx = 0;

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

        int file_idx = 0;
        File *dir_files;

        while ((nde = readdir(ndir)) != NULL) {
            int file_type = nde->d_type;
            char *file_name = nde->d_name;
            if (file_type == FILE_TYPE_CODE) {
                char *paths[] = { (char *)DIR_PATH, de->d_name, nde->d_name};
                char *full_path = build_file_path(paths, 3, "");
                char *file_contents = read_file_contents(full_path);
                int file_path_size = strlen(full_path) + 1;
                int file_contents_size = strlen(file_contents) + 1;

                if (file_idx == 0) {
                    dir_files = malloc(sizeof(File));
                } else {
                    dir_files = realloc(dir_files, (file_idx + 1) * sizeof(File));
                }         

                dir_files[file_idx].file_type = strcmp(file_name, README_FILE_NM) == 0 ? README:EXERCISE;
                dir_files[file_idx].file_path = malloc(file_path_size);
                strcpy(dir_files[file_idx].file_path, full_path);
                dir_files[file_idx].file_contents = malloc(file_contents_size);
                strcpy(dir_files[file_idx].file_contents, file_contents);

                file_idx++;

                free(full_path);
                free(file_contents);
            }
        }

        add_dir(dirs, dir_files, file_idx, dir_idx);

        dir_idx++;
        closedir(ndir);
        free(nested_path);
    }

    closedir(dir);
}

int main() {
    Directory *dirs = malloc(TOTAL_EXERCISES_DIRS * sizeof(Directory));
    if (dirs == NULL) {
        perror("Failed allocate memory for dirs");
        exit(1);
    }

    load_files(&dirs);

    for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
        for (int e = 0; e < dirs[i].file_ct; e++) {
            printf("File path: %s \n", dirs[i].files[e].file_path); 
            printf("File type: %i \n", dirs[i].files[e].file_type); 
            printf("exercise contents: %s \n", dirs[i].files[e].file_contents);
            
        }
    }

    // cleanup 
    for (int i = 0; i < TOTAL_EXERCISES_DIRS; i++) {
        for (int e = 0; e < dirs[i].file_ct; e++) {
            free(dirs[i].files[e].file_path);
            free(dirs[i].files[e].file_contents);
        }
    }

    free(dirs);

    return 0;
}
