#ifndef RUNNA
#define RUNNA

int exec_cmd(char *command);
int exec_compile(char *file_path, char *file_name_no_ext);
/// executes binary at a default location "./bin" expecting no file extension
int exec_run(char *file_name_no_ext);

#endif
