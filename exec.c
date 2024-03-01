#include "main.h"

/**
 * execute_command - executes the argument
 *
 * @command_line: the command exectuted
 *
 * return: 0
 */

void execute_command(char *command_line)
{
	char **argv;
	int argc;
	pid_t pid;

	argv = tokenize_command(command_line, &argc);

	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		free_argv(argv, argc);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("execvp");
			free_argv(argv, argc);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		free_argv(argv, argc);
	}
}

/**
 * tokenize_command - creates tokens of command line into arguments
 *
 * @command_line: command line to tokenize
 * @argc: pointer to store the number of arguments
 *
 * Return: argv
 */

char **tokenize_command(char *command_line, int *argc)
{
	char *token;
	char **argv;
	int count = 0;
	int i;
	int j;

	token = strtok(command_line, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}
	*argc = count;

	argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(command_line, " ");
	for (i = 0; i < count; i++)
	{
		argv[i] = malloc(strlen(token) + 1);
		if (argv[i] == NULL)
		{
			perror("malloc");
			for (j = 0; j < i; j++)
			{
				free(argv[j]);
			}
			free(argv);
			exit(EXIT_FAILURE);
		}
		strcpy(argv[i], token);
		token = strtok(NULL, " ");
	}
	argv[count] = NULL;
	return (argv);
}

/**
 * free_argv - free memory allocated to argv
 *
 * @argv: array of pointers to arguments
 * @argc: number of arguments
 *
 * return: 0
 */

void free_argv(char **argv, int argc)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		free(argv[i]);
	}
	free(argv);
}
