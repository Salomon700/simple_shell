#include "main.h"

/**
 * get_parent_process_id - gets process ID of parent for current process
 *
 * Return: parent process ID
 */

pid_t get_parent_process_id(void)
{
	return (getppid());
}
