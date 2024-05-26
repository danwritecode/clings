#include "runna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LINES = 500;
int exec_cmd(char *command) {
	FILE *fp;
	int status;
	char path[MAX_LINES];

	fp = popen(command, "w");
	if (fp == NULL) {
		perror("Failed to execution popen command");
		exit(1);
	}

	while (fgets(path, MAX_LINES, fp) != NULL)
		printf("%s", path);

	status = pclose(fp);
	if (status == -1) {
		perror("Failed to close");
		exit(1);
	}

	if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

	return -1;
}

int exec_compile(char *file_path) {
    int path_len = strlen(file_path);
    int buff_size = path_len + (path_len - 2) + 35; // 35 is for gcc flags and other stuff

    // create snprintf buffer
    char *compile_cmd = malloc(buff_size);

    // create buffer for filename slicing
    char *file_path_no_ext = malloc(path_len - 2);
    strncpy(file_path_no_ext, file_path, path_len - 2);

    snprintf(compile_cmd, buff_size, "gcc %s -o %s%s -Wall -Wextra -Werror", file_path, file_path_no_ext, ".bin");
	printf("cmd: %s \n", compile_cmd);

    return exec_cmd(compile_cmd);
}
