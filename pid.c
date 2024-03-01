#include "main.h"

/**
 * get_process_id - get the process ID of the current process
 *
 * Return: process ID
 */

pid_t get_process_id(void)
{
	return (getpid());
}
