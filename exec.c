#include "main.h"

/**
 * execute_command - executes given command
 *
 * @command: command to execute
 *
 * Return: 0
 */

void execute_command(char *command)
{
	char command_path[256];
	snprintf(command_path, sizeof(command_path), "./%s", command);

	if (access(command, X_OK) != 0)
	{
		fprintf(stderr, "%s: No such file or directory\n", command_path);
	}
	else
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char **argv = malloc(2 * sizeof(char *));

			if (argv == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			argv[0] = command;
			argv[1] = NULL;
			if (execve(command, argv, NULL) == -1)
			{
				perror("execve");
				free(argv);
				exit(EXIT_FAILURE);
			}
			free(argv);
		}
		else
		{
			wait(NULL);
		}
	}
}
