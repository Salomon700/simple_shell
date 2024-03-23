#include "shell.h"

/**
 * print_env_vars - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_env_vars(info_t *info)
{
    print_list_strings(info->env_list);
    return (0);
}

/**
 * get_env_var - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_env_var(info_t *info, const char *name)
{
    list_t *node = info->env_list;
    char *p;

    while (node)
    {
        p = starts_with_str(node->str_val, name);
        if (p && *p)
            return (p);
        node = node->next_node;
    }
    return (NULL);
}

/**
 * set_env_var - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int set_env_var(info_t *info)
{
    if (info->argc_val != 3)
    {
        write_str_to_fd("Incorrect number of arguements\n", 2);
        return (1);
    }
    if (add_env_var(info, info->argv_arr[1], info->argv_arr[2]))
        return (0);
    return (1);
}

/**
 * unset_env_var - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unset_env_var(info_t *info)
{
    int i;

    if (info->argc_val == 1)
    {
        write_str_to_fd("Too few arguements.\n", 2);
        return (1);
    }
    for (i = 1; i <= info->argc_val; i++)
        remove_env_var(info, info->argv_arr[i]);

    return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; env_vars[i]; i++)
        add_node_to_end(&node, env_vars[i], 0);
    info->env_list = node;
    return (0);
}
