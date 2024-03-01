#include "main.h"

/**
 * handle_fork_error- handles errors that occur in forking
 *
 * Return:0
 */

void handle_fork_error(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
}
