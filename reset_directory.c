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
// nuke the working directory and copy the master directory to it
// need to test on each exercise

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

int main() {
	reset_directory("./master_exercises_read_only", "./exercises");
	printf("Reset complete!\n");
	return 0;
}