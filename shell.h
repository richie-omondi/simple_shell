#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ;

/******* Structs **********/

/**
 * struct data - struct for data fed to the shell
 * @exe: executable file
 * @input: pointer to the input
 * @command: pointer to a command typed by the user
 * @fd: file descriptor
 * @tokens: tokenized input
 * @env: environ
 * @no_of_executions: no of shhell executions
 */
typedef struct data
{
	char *exe;
	char *input;
	char *command;
	char **tokens;
	char **env;
	int no_of_executions;
	int fd;
} shell_data;

/****** Prototypes *****/

/****** Implement the shell ******/
void shell_loop(shell_data *shell);
int read_input(shell_data *shell, size_t buffer_size);
char **split_input(shell_data *shell);
char *handle_path(shell_data *shell);
int check_file(char *path);
int is_exe(shell_data *shell);
int compare_env_var(char *variable, char *name);
char *get_env_value(char *variable, shell_data *shell);
int execute_commands(shell_data *shell);
void add_data_to_shell(shell_data *shell, int ac, char *av[]);
char *malloc_string(char *string);
int int_length(int n);
char *_itoa(int n);
int check_execute_permissions(char *path, shell_data *shell);
void handle_signal(int signal);

/******* Print functions ********/
int print_string(char *s);
int print_e(char *string);
int print_error(int error, shell_data *shell);
int str_cmp(char *s1, char *s2);

/****** Memory functions *******/
void *_calloc(unsigned int nmem, unsigned int size);
void free_shell_data(shell_data *shell);
void free_without_input(shell_data *shell);

/******** String functions *******/
int str_len(char *string);
char *str_dup(char *string);
char *str_cpy(char *dest, char *src);
char *str_cat(char *dest, char *src);
int _strncmp(char *str1, char *str2, size_t n);

#endif
