#include "shell.h"

/**
 * show_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int show_history(info_t *info)
{
    print_list_elements(info->history_list);
    return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = find_char(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias_list),
        get_node_index(info->alias_list, find_node_starts_with(info->alias_list, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = find_char(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_to_end(&(info->alias_list), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = find_char(node->str_val, '=');
        for (a = node->str_val; a <= p; a++)
            print_char(*a);
        print_char('\'');
        print_string(p + 1);
        print_string("'\n");
        return (0);
    }
    return (1);
}

/**
 * handle_aliases - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int handle_aliases(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc_val == 1)
    {
        node = info->alias_list;
        while (node)
        {
            print_alias(node);
            node = node->next_node;
        }
        return (0);
    }
    for (i = 1; info->argv_arr[i]; i++)
    {
        p = find_char(info->argv_arr[i], '=');
        if (p)
            set_alias(info, info->argv_arr[i]);
        else
            print_alias(find_node_starts_with(info->alias_list, info->argv_arr[i], '='));
    }

    return (0);
}
