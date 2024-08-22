#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

void copy_file(const char *src, const char *dest) {
    int source_fd = open(src, O_RDONLY);
    int dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(source_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes);
    }
    close(source_fd);
    close(dest_fd);
}

void remove_directory_contents(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    struct dirent *entry;
    char file_path[1024];

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
        
        struct stat path_stat;
        stat(file_path, &path_stat);
        
        if (S_ISDIR(path_stat.st_mode)) {
            remove_directory_contents(file_path);
            rmdir(file_path);
        } else {
            unlink(file_path);
        }
    }

    closedir(dir);
}

void reset_directory(const char *master, const char *working) {
    remove_directory_contents(working);

    DIR *dir = opendir(master);
    struct dirent *entry;
    char src_path[1024], dest_path[1024];

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(src_path, sizeof(src_path), "%s/%s", master, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", working, entry->d_name);
        
        struct stat path_stat;
        stat(src_path, &path_stat);
        
        if (S_ISDIR(path_stat.st_mode)) {
            mkdir(dest_path, 0755);
            reset_directory(src_path, dest_path);
        } else {
            copy_file(src_path, dest_path);
        }
    }

    closedir(dir);
}

void reset_exercise(int exercise_number) {
    DIR *master_dir = opendir("./master_exercises_read_only");
    DIR *working_dir = opendir("./exercises");
    struct dirent *entry;
    char number_prefix[3];
    int exercises_reset = 0;

    if (master_dir == NULL || working_dir == NULL) {
        perror("opendir");
        return;
    }

    snprintf(number_prefix, sizeof(number_prefix), "%02d", exercise_number);

    printf("Resetting exercise(s) starting with %s...\n", number_prefix);

    while ((entry = readdir(master_dir)) != NULL) {
        if (strncmp(entry->d_name, number_prefix, 2) == 0) {
            char full_master_path[1024], full_working_path[1024];
            snprintf(full_master_path, sizeof(full_master_path), "./master_exercises_read_only/%s", entry->d_name);
            snprintf(full_working_path, sizeof(full_working_path), "./exercises/%s", entry->d_name);
            
            printf("Resetting: %s\n", entry->d_name);
            reset_directory(full_master_path, full_working_path);
            exercises_reset++;
        }
    }

    closedir(master_dir);
    closedir(working_dir);

    if (exercises_reset > 0) {
        printf("Reset complete for %d exercise(s) starting with %s!\n", exercises_reset, number_prefix);
    } else {
        printf("No exercises found starting with %s.\n", number_prefix);
    }
}

int main() {
    // nuke or choose
    int exercise_number;
    printf("Enter the exercise number you want to reset ex '01' (or 0 to reset all): ");
    scanf("%d", &exercise_number);

    if (exercise_number == 0) {
        printf("Are you sure you want to reset all exercises? This will delete all progress. (y/n): ");
        char response;
        scanf(" %c", &response);
        if (response != 'y' && response != 'Y') {
            printf("Reset cancelled.\n");
            return 0;
        }
        reset_directory("./master_exercises_read_only", "./exercises");
        printf("All exercises have been reset!\n");
    } else {
        printf("Are you sure you want to reset exercise(s) starting with %02d? This will delete all progress for these exercise(s). (y/n): ", exercise_number);
        char response;
        scanf(" %c", &response);
        if (response != 'y' && response != 'Y') {
            printf("Reset cancelled.\n");
            return 0;
        }
        reset_exercise(exercise_number);
    }

    return 0;
}
