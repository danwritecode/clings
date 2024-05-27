#include "runna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIN_PATH "./bin"

const int MAX_LINES = 500;
int exec_cmd(char *command) {
	FILE *fp;
	int status;

	fp = popen(command, "w");
	if (fp == NULL) {
		perror("Failed to execution popen command");
		exit(1);
	}

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

int exec_cmd_output(char *command) {
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

int exec_compile_output(char *file_path, char *file_name_no_ext) {
    int path_len = strlen(file_path);
    int file_name_len = strlen(file_name_no_ext);
    int buff_size = path_len + file_name_len + 45; // 35 is for gcc flags and other stuff

    // create snprintf buffer
    char *compile_cmd = malloc(buff_size);
    snprintf(compile_cmd, buff_size, "gcc %s -o %s/%s -Wall -Wextra -Werror", file_path, BIN_PATH ,file_name_no_ext);

    int res_code = exec_cmd_output(compile_cmd);

	free(compile_cmd);
	return res_code;
}

int exec_run_output(char *file_name_no_ext) {
	int file_path_size = strlen(file_name_no_ext) + 7;
	char *file_path = malloc(file_path_size); // add 5 for binary path
	snprintf(file_path, file_path_size, "%s/%s", BIN_PATH, file_name_no_ext);
    int res_code = exec_cmd_output(file_path);

	free(file_path);
	return res_code;
}

int exec_compile(char *file_path, char *file_name_no_ext) {
    int path_len = strlen(file_path);
    int file_name_len = strlen(file_name_no_ext);
    int buff_size = path_len + file_name_len + 45; // 35 is for gcc flags and other stuff

    // create snprintf buffer
    char *compile_cmd = malloc(buff_size);
    snprintf(compile_cmd, buff_size, "gcc %s -o %s/%s -Wall -Wextra -Werror", file_path, BIN_PATH ,file_name_no_ext);

    int res_code = exec_cmd(compile_cmd);

	free(compile_cmd);
	return res_code;
}

int exec_run(char *file_name_no_ext) {
	int file_path_size = strlen(file_name_no_ext) + 7;
	char *file_path = malloc(file_path_size); // add 5 for binary path
	snprintf(file_path, file_path_size, "%s/%s", BIN_PATH, file_name_no_ext);
    int res_code = exec_cmd(file_path);

	free(file_path);
	return res_code;
}
