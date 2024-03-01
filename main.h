#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void display_prompt(void);
void execute_command(char *command);
void handle_fork_error(void);
pid_t get_process_id(void);
pid_t get_parent_process_id(void);
void wait_for_child(void);

#endif
