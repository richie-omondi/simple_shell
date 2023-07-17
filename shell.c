#include "shell.h"

/**
 * main - Entry point for the program
 * @ac: argument count
 * @av: array containing arguments fed to the shell
 * @env: environment variables
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	shell_data shell_info = { NULL };
	shell_data *shell = &shell_info;

	add_data_to_shell(shell, ac, av, env);
	shell_loop(shell);

	return (EXIT_SUCCESS);
}

/**
 * shell_loop - Function that implements looping-like functionality
 * of the shell
 * @shell: struct containing data fd to the shell
 *
 * Return: 0 on success
*/
void shell_loop(shell_data *shell)
{
	char *shell_sign = "($)";

	while (1)
	{
		print_string(shell_sign);

		read_input(shell);
		split_input(shell);
		execute_commands(shell);

		free_and_close(shell);
	}
}

/**
 * read_input - Reads the input typed by the user
 * @shell: Struct containing data fed to the shell
 *
 * Return: input fed to the shell
 */
char *read_input(shell_data *shell)
{
	size_t buffer_size;

	int result;

	shell->input = NULL;

	buffer_size = 0;

	result = getline(&(shell->input), &buffer_size, stdin);

	if (result == -1)
	{
		if (result == EOF)
			exit(errno);
		else
		{
			perror("Read input");
			exit(EXIT_FAILURE);
		}
	}

	return (shell->input);
}

/**
 * split_input - tokenizes a string
 * @shell: struct containing data fed to the shell
 *
 * Return: individual tokens
 */
char **split_input(shell_data *shell)
{
	int buffer_size = BUFFER_SIZE;

	int index;

	char *token;

	int i;

	char **temp;

	index = 0;

	shell->tokens = malloc(buffer_size * sizeof(char *));

	if (!(shell->tokens))
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(shell->input, DELIMITERS);

	while (token != NULL)
	{
		shell->tokens[index] = token;
		index++;

		if (index >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			temp = malloc(buffer_size * sizeof(char *));

			if (!temp)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			for (i = 0; i < index; i++)
			{
				temp[i] = shell->tokens[i];
			}
			free(shell->tokens);
			shell->tokens = temp;
		}
		token = strtok(NULL, DELIMITERS);
	}
	shell->tokens[index] = NULL;
	return (shell->tokens);
}
