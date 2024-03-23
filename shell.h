Here's the modified version of the shell.h file with variable and function names changed:

```c
#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define NORMAL_COMMAND 0
#define OR_COMMAND 1
#define AND_COMMAND 2
#define CHAIN_COMMAND 3

/* for convert_num() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".my_shell_history"
#define HISTORY_MAX 4096

extern char **env_vars;


/**
 * struct linked_list - singly linked list
 * @num_val: the number field
 * @str_val: a string
 * @next_node: points to the next node
 */
typedef struct linked_list
{
    int num_val;
    char *str_val;
    struct linked_list *next_node;
} list_t;

/**
 *struct pass_info - contains pseudo-arguements to pass into a function,
 *        allowing uniform prototype for function pointer struct
 *@arg_str: a string generated from getline containing arguements
 *@argv_arr: an array of strings generated from arg_str
 *@path_str: a string path for the current command
 *@argc_val: the argument count
 *@line_count_val: the error count
 *@err_num_val: the error code for exit()s
 *@linecount_flag_val: if on count this line of input
 *@fname_str: the program filename
 *@env_list: linked list local copy of environ
 *@environ_arr: custom modified copy of environ from LL env
 *@history_list: the history node
 *@alias_list: the alias node
 *@env_changed_val: on if environ was changed
 *@status_val: the return status of the last exec'd command
 *@cmd_buf_ptr: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type_val: CMD_type ||, &&, ;
 *@readfd_val: the fd from which to read line input
 *@histcount_val: the history line number count
 */
typedef struct pass_info
{
    char *arg_str;
    char **argv_arr;
    char *path_str;
    int argc_val;
    unsigned int line_count_val;
    int err_num_val;
    int linecount_flag_val;
    char *fname_str;
    list_t *env_list;
    list_t *history_list;
    list_t *alias_list;
    char **environ_arr;
    int env_changed_val;
    int status_val;

    char **cmd_buf_ptr; /* pointer to cmd ; chain buffer, for memory mangement */
    int cmd_buf_type_val; /* CMD_type ||, &&, ; */
    int readfd_val;
    int histcount_val;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 *struct builtin_cmd - contains a builtin string and related function
 *@type_str: the builtin command flag
 *@func_ptr: the function
 */
typedef struct builtin_cmd
{
    char *type_str;
    int (*func_ptr)(info_t *);
} builtin_table;


/* toem_shloop.c */
int run_shell(info_t *, char **);
int find_builtin_cmd(info_t *);
void find_and_run_cmd(info_t *);
void fork_and_run_cmd(info_t *);

/* toem_parser.c */
int is_valid_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path_cmd(info_t *, char *, char *);

/* loophsh.c */
int loop_shell(char **);

/* toem_errors.c */
void print_error_str(char *);
int print_error_char(char);
int write_to_fd(char c, int fd);
int write_str_to_fd(char *str, int fd);

/* toem_string.c */
int get_str_len(char *);
int compare_strings(char *, char *);
char *starts_with_str(const char *, const char *);
char *concatenate_strings(char *, char *);

/* toem_string1.c */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_char(char);

/* toem_exits.c */
char *copy_n_chars(char *, char *, int);
char *concatenate_n_chars(char *, char *, int);
char *find_char(char *, char);

/* toem_tokenizer.c */
char **split_string(char *, char *);
char **split_string_2(char *, char);

/* toem_realloc.c */
char *set_memory(char *, char, unsigned int);
void free_string_array(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* toem_memory.c */
int free_ptr(void **);

/* toem_atoi.c */
int is_interactive_mode(info_t *);
int is_delim_char(char, char *);
int is_alpha_char(int);
int convert_to_int(char *);

/* toem_errors1.c */
int convert_error_to_int(char *);
void print_error_message(info_t *, char *);
int print_decimal(int, int);
char *convert_num_to_string(long int, int, int);
void remove_comments_from_string(char *);

/* toem_builtin.c */
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);

/* toem_builtin1.c */
int show_history(info_t *);
int handle_aliases(info_t *);

/*toem_getline.c */
ssize_t get_input_line(info_t *);
int get_line(info_t *, char **, size_t *);
void handle_sigint(int);

/* toem_getinfo.c */
void clear_info_struct(info_t *);
void set_info_struct(info_t *, char **);
void free_info_struct(info_t *, int);

/* toem_environ.c */
char *get_env_var(info_t *, const char *);
int print_env_vars(info_t *);
int set_env_var(info_t *);
int unset_env_var(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ_array(info_t *);
int remove_env_var(info_t *, char *);
int add_env_var(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file_path(info_t *info);
int write_history_to_file(info_t *info);
int read_history_from_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history_list(info_t *info);

/* toem_lists.c */
list_t *add_node_to_list(list_t **, const char *, int);
list_t *add_node_to_end(list_t **, const char *, int);
size_t print_list_strings(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_linked_list(list_t **);

/* toem_lists1.c */
size_t get_list_length(const list_t *);
char **convert_list_to_strings(list_t *);
size_t print_list_elements(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain_operation(info_t *, char *, size_t *);
void check_chain_operation(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_with_value(info_t *);
int replace_vars_with_values(info_t *);
int replace_string_in_array(char **, char *);

#endif
