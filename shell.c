#include "main.h"

/**
 * main - simple commmand line interpreter
 *
 * Return: 0
 */

int main(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nchars_read;

	while (1)
	{
		display_prompt();
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				free(lineptr);
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("getline");
				free(lineptr);
				exit(EXIT_FAILURE);
			}
		}
		if (lineptr[nchars_read - 1] == '\n')
			lineptr[nchars_read - 1] = '\0';
		if (strcmp(lineptr, "exit") == 0)
		{
			free(lineptr);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute_command(lineptr);
		}
		free(lineptr);
		lineptr = NULL;
	}
	return (0);
}
