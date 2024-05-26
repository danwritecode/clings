#ifndef FILES
#define FILES

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    EXERCISE,
    README
} FileType;

typedef struct {
    char *file_path;
    char *parent_dir_path;
    char *file_contents;
    bool file_diff;
    FileType file_type;
} File;

typedef struct {
    File *files;
    size_t file_ct;
} Directory;

/// This assumes that any path does not contain any dividers
/// *base_path = "../" or "./" or "/" if needed, otherwise pass ""
char* build_file_path(char **paths, int size, char *base_path);
char* read_file_contents(char *file_path);
void add_dir(Directory **dirs, File *files, int file_ct, int dir_idx);
void load_files(Directory **dirs);

#endif
