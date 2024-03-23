#include "shell.h"

/**
 * get_environ_array - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ_array(info_t *info)
{
    if (!info->environ_arr || info->env_changed_val)
    {
        info->environ_arr = convert_list_to_strings(info->env_list);
        info->env_changed_val = 0;
    }

    return (info->environ_arr);
}

/**
 * remove_env_var - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int remove_env_var(info_t *info, char *var)
{
    list_t *node = info->env_list;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with_str(node->str_val, var);
        if (p && *p == '=')
        {
            info->env_changed_val = delete_node_at_index(&(info->env_list), i);
            i = 0;
            node = info->env_list;
            continue;
        }
        node = node->next_node;
        i++;
    }
    return (info->env_changed_val);
}

/**
 * add_env_var - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int add_env_var(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(get_str_len(var) + get_str_len(value) + 2);
    if (!buf)
        return (1);
    copy_string(buf, var);
    concatenate_strings(buf, "=");
    concatenate_strings(buf, value);
    node = info->env_list;
    while (node)
    {
        p = starts_with_str(node->str_val, var);
        if (p && *p == '=')
        {
            free(node->str_val);
            node->str_val = buf;
            info->env_changed_val = 1;
            return (0);
        }
        node = node->next_node;
    }
    add_node_to_end(&(info->env_list), buf, 0);
    free(buf);
    info->env_changed_val = 1;
    return (0);
}
