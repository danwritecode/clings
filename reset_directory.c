#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

void copy_file(const char *src, const char *dest) {
    int source_fd = open(src, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return;
    }
    int dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return;
    }
    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(source_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes) != bytes) {
            perror("Error writing to destination file");
            break;
        }
    }
    if (bytes == -1) {
        perror("Error reading from source file");
    }
    close(source_fd);
    close(dest_fd);
}

void remove_directory_contents(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }
    struct dirent *entry;
    char file_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
        
        struct stat path_stat;
        if (stat(file_path, &path_stat) == -1) {
            perror("Error getting file status");
            continue;
        }
        
        if (S_ISDIR(path_stat.st_mode)) {
            remove_directory_contents(file_path);
            if (rmdir(file_path) == -1) {
                perror("Error removing directory");
            }
        } else {
            if (unlink(file_path) == -1) {
                perror("Error removing file");
            }
        }
    }

    closedir(dir);
}

void reset_directory(const char *master, const char *working) {
    remove_directory_contents(working);

    DIR *dir = opendir(master);
    if (dir == NULL) {
        perror("Error opening master directory");
        return;
    }
    struct dirent *entry;
    char src_path[1024], dest_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(src_path, sizeof(src_path), "%s/%s", master, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", working, entry->d_name);
        
        struct stat path_stat;
        if (stat(src_path, &path_stat) == -1) {
            perror("Error getting file status");
            continue;
        }
        
        if (S_ISDIR(path_stat.st_mode)) {
            if (mkdir(dest_path, 0755) == -1) {
                perror("Error creating directory");
                continue;
            }
            reset_directory(src_path, dest_path);
        } else {
            copy_file(src_path, dest_path);
        }
    }

    closedir(dir);
}

int get_confirmation(const char *message) {
    char response;
    printf("%s (y/n): ", message);
    scanf(" %c", &response);
    return response == 'y' || response == 'Y';
}

void reset_exercise(int exercise_number) {
    DIR *master_dir = opendir("./master_exercises_read_only");
    if (master_dir == NULL) {
        perror("Error opening master directory");
        return;
    }
    DIR *working_dir = opendir("./exercises");
    if (working_dir == NULL) {
        perror("Error opening working directory");
        closedir(master_dir);
        return;
    }
    struct dirent *entry;
    char number_prefix[3];
    int exercises_reset = 0;

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
    char input[10];
    int exercise_number;

    printf("Enter the exercise number you want to reset (00-99, or 0 to reset all): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = 0;

    if (strlen(input) > 2 || !isdigit(input[0]) || (strlen(input) == 2 && !isdigit(input[1]))) {
        fprintf(stderr, "Invalid input. Please enter a number between 00 and 99, or 0.\n");
        return 1;
    }

    exercise_number = atoi(input);

    if (exercise_number == 0) {
        if (!get_confirmation("Are you sure you want to reset all exercises? This will delete all progress")) {
            printf("Reset cancelled.\n");
            return 0;
        }
        reset_directory("./master_exercises_read_only", "./exercises");
        printf("All exercises have been reset!\n");
    } else if (exercise_number > 0 && exercise_number <= 99) {
        char confirm_message[120];
        snprintf(confirm_message, sizeof(confirm_message), 
                 "Are you sure you want to reset exercise(s) %02d? This will delete all progress for these exercise(s)", 
                 exercise_number);

        if (!get_confirmation(confirm_message)) {
            printf("Reset cancelled.\n");
            return 0;
        }
        reset_exercise(exercise_number);
    } else {
        fprintf(stderr, "Invalid exercise number. Please enter a number between 01 and 99, or 0 for all exercises.\n");
        return 1;
    }

    return 0;
}
