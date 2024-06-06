#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "files.h"

const char DIR_PATH[] = "./exercises";
const int DIR_TYPE_CODE = 4;
const int FILE_TYPE_CODE = 8;
const char README_FILE_NM[] = "README.md";


/// This assumes that any path does not contain any dividers
/// *base_path = "../" or "./" or "/" if needed, otherwise pass ""
char* build_file_path(char **paths, int size, char *base_path) {
    // calculate the total length needed for the concatenated path
    int str_len = strlen(base_path) + 1;
    for (int i = 0; i < size; i++) {
        str_len += strlen(paths[i]) + 1;
    }

    char *str_buff = malloc(str_len);
    if (str_buff == NULL) {
        printf("concat_path_dyn malloc failed");
        exit(1);
    }

    // initialize the buffer with base_path
    strcpy(str_buff, base_path);

    for (int i = 0; i < size; i++) {
        strcat(str_buff, paths[i]);
        if (i < size - 1) {
            strcat(str_buff, "/");
        }
    }

    return str_buff;
}


char* read_file_contents(char *file_path) {
    struct stat fstat_buff;
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    if (fstat(fileno(file), &fstat_buff) == -1) {
        perror("Failed to get file stats");
        fclose(file);
        exit(1);

    }
    long file_size = fstat_buff.st_size;
    char *file_buff = malloc(file_size + 1);

    if (file_buff == NULL) {
        perror("Failed to allocate memory for reading file");
        fclose(file);
        exit(1);
    }

    fread(file_buff, 1, file_size, file);
    file_buff[file_size] = '\0';
    fclose(file);

    return file_buff;
}

bool is_marked_incompleted(char *file_contents, int file_contents_size) {
    char x1 = 0xE2, x2 = 0x9D, x3 = 0x8C; // UTF-8 encoding of '❌'

    for (int i = 0; i < file_contents_size - 3; i++) {
        char c1 = file_contents[i];
        char c2 = file_contents[i + 1];
        char c3 = file_contents[i + 2];

        if (c1 == x1 && c2 == x2 && c3 == x3) return true;
    }

    return false;
}

void add_dir(FileCollection **dirs, File *files, int file_ct, int dir_idx) {
    dirs[dir_idx] = malloc(sizeof(FileCollection));
    dirs[dir_idx]->files = malloc(sizeof(File) * file_ct);

    if (dirs[dir_idx]->files == NULL) {
        perror("Failed to allocate memory for files in dir");
        exit(1);
    }


    for (int i = 0; i < file_ct; i++) {
        dirs[dir_idx]->files[i].file_path = strdup(files[i].file_path);
        dirs[dir_idx]->files[i].file_name = strdup(files[i].file_name);
        dirs[dir_idx]->files[i].file_name_no_ext = strdup(files[i].file_name_no_ext);
        dirs[dir_idx]->files[i].parent_dir_path = strdup(files[i].parent_dir_path);
        dirs[dir_idx]->files[i].file_contents = strdup(files[i].file_contents);
        dirs[dir_idx]->files[i].file_type = files[i].file_type;
        dirs[dir_idx]->files[i].marked_incomplete = files[i].marked_incomplete;
        dirs[dir_idx]->files[i].file_diff = files[i].file_diff;
    }

    dirs[dir_idx]->file_ct = file_ct;
}


int alphasort(const struct dirent **a, const struct dirent **b) {
    return strcasecmp((*a)->d_name, (*b)->d_name);
}


/// Loops through target directory path and loads files into Directory double pointer and returns total exercise files
int load_files(FileCollection **dirs) {
    struct dirent **nmlist;
    int ex_dirs_ct = scandir(DIR_PATH, &nmlist, NULL, alphasort);

    if (ex_dirs_ct < 0) {
        perror("Could not open directory");
        exit(1);
    }

    int dir_idx = 0;
    int total_exercise_file_ct = 0;

    for (int di = 0; di < ex_dirs_ct; di++) {
        struct dirent *de = nmlist[di];
        int file_type = de->d_type;

        if (file_type != DIR_TYPE_CODE) continue;
        if (strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".") == 0) continue;

        // expecting only directories here at 1 layer depth, not using recursion cause lazy
        char *paths[] = { (char *)DIR_PATH, de->d_name };
        char *nested_path = build_file_path(paths, 2, "");

        struct dirent **nmlist_nested;
        int ex_dirs_nested_ct = scandir(nested_path, &nmlist_nested, NULL, alphasort);

        if (ex_dirs_nested_ct < 0) {
            perror("Could not open directory");
            exit(1);
        }

        int file_idx = 0; // need this because not everything in a directory is an exercise file
        int exercise_file_ct = 0;
        File *dir_files;

        for (int ndi = 0; ndi < ex_dirs_nested_ct; ndi++) {
            struct dirent *nde = nmlist_nested[ndi];
            int file_type = nde->d_type;
            char *file_name = nde->d_name;

            if (file_type == FILE_TYPE_CODE) {
                char *paths[] = { (char *)DIR_PATH, de->d_name, nde->d_name};
                char *full_path = build_file_path(paths, 3, "");
                char *file_contents = read_file_contents(full_path);
                int dir_path_size = strlen(nested_path) + 1;
                int file_path_size = strlen(full_path) + 1;
                int file_name_size = strlen(file_name) + 1;
                int file_contents_size = strlen(file_contents) + 1;
                int file_type = strcmp(file_name, README_FILE_NM) == 0 ? README:EXERCISE;

                if (file_idx == 0) {
                    dir_files = malloc(sizeof(File));
                } else {
                    dir_files = realloc(dir_files, (file_idx + 1) * sizeof(File));
                }         

                // file type
                dir_files[file_idx].file_type = file_type;

                // file path
                dir_files[file_idx].file_path = malloc(file_path_size);
                strcpy(dir_files[file_idx].file_path, full_path);

                // file name
                dir_files[file_idx].file_name = malloc(file_name_size);
                strcpy(dir_files[file_idx].file_name, file_name);

                if (file_type == EXERCISE) {
                    // create file name no extension
                    dir_files[file_idx].file_name_no_ext = malloc(file_name_size - 2);
                    strncpy(dir_files[file_idx].file_name_no_ext, file_name, file_name_size - 3);
                    dir_files[file_idx].file_name_no_ext[file_name_size - 3] = '\0';

                    // check to see if user has marked exercise as completed
                    bool marked_complete = is_marked_incompleted(file_contents, file_contents_size);
                    dir_files[file_idx].marked_incomplete = marked_complete;

                    exercise_file_ct++;
                } else if (file_type == README) {
                    dir_files[file_idx].file_name_no_ext = malloc(file_name_size - 2);
                    strncpy(dir_files[file_idx].file_name_no_ext, file_name, file_name_size - 4);
                    dir_files[file_idx].file_name_no_ext[file_name_size - 4] = '\0';

                    // set completeness flag
                    dir_files[file_idx].marked_incomplete = false;
                } else {
                    dir_files[file_idx].file_name_no_ext = malloc(file_name_size);
                    strcpy(dir_files[file_idx].file_name_no_ext, file_name);

                    // set completeness flag
                    dir_files[file_idx].marked_incomplete = false;
                }

                // dir path
                dir_files[file_idx].parent_dir_path = malloc(dir_path_size);
                strcpy(dir_files[file_idx].parent_dir_path, nested_path);

                // get existing file contents to find if there's a diff
                if (dirs[dir_idx] != NULL) {
                    char *old_file_contents = dirs[dir_idx]->files[file_idx].file_contents;
                    if (strcmp(file_contents, old_file_contents) != 0) {
                        dir_files[file_idx].file_diff = true;
                    } else {
                        dir_files[file_idx].file_diff = false;
                    }
                } else {
                    dir_files[file_idx].file_diff = false;
                }

                // file contents
                dir_files[file_idx].file_contents = malloc(file_contents_size);
                strcpy(dir_files[file_idx].file_contents, file_contents);

                file_idx++;

                free(full_path);
                free(file_contents);
            }
        }

        add_dir(dirs, dir_files, file_idx, dir_idx);
        total_exercise_file_ct += exercise_file_ct;

        // free dir_files
        for (int i = 0; i < file_idx; i++) {
            free(dir_files[i].parent_dir_path);
            free(dir_files[i].file_path);
            free(dir_files[i].file_contents);
            free(dir_files[i].file_name);
            free(dir_files[i].file_name_no_ext);
        }

        dir_idx++;
        free(nested_path);
        free(nmlist_nested);
    }

    free(nmlist);

    return total_exercise_file_ct;
}
