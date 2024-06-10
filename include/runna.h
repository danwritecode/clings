#ifndef RUNNA_H
#define RUNNA_H

int exec_cmd(char *command);
int exec_cmd_output(char *command);

/// compiles C file at path given with output and returns exit code
int exec_compile_output(char *file_path, char *file_name_no_ext);
/// compiles C file at path given with no output and returns exit code
int exec_compile(char *file_path, char *file_name_no_ext);

/// executes binary at a default location "./bin" expecting no file extension with command output and returns exit code
int exec_run_output(char *file_name_no_ext);
/// executes binary at a default location "./bin" expecting no file extension with no output and returns exit code
int exec_run(char *file_name_no_ext);

int exec_clear_bin();
#endif
