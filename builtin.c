#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv_arr[0] != "exit"
 */
int exit_shell(info_t *info)
{
    int exit_check;

    if (info->argv_arr[1])  /* If there is an exit arguement */
    {
        exit_check = convert_error_to_int(info->argv_arr[1]);
        if (exit_check == -1)
        {
            info->status_val = 2;
            print_error_message(info, "Illegal number: ");
            write_str_to_fd(info->argv_arr[1], 2);
            print_error_char('\n');
            return (1);
        }
        info->err_num_val = convert_error_to_int(info->argv_arr[1]);
        return (-2);
    }
    info->err_num_val = -1;
    return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_directory(info_t *info)
{
    char *curr_dir, *new_dir, buffer[1024];
    int chdir_ret;

    curr_dir = getcwd(buffer, 1024);
    if (!curr_dir)
        print_string("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv_arr[1])
    {
        new_dir = get_env_var(info, "HOME=");
        if (!new_dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((new_dir = get_env_var(info, "PWD=")) ? new_dir : "/");
        else
            chdir_ret = chdir(new_dir);
    }
    else if (compare_strings(info->argv_arr[1], "-") == 0)
    {
        if (!get_env_var(info, "OLDPWD="))
        {
            print_string(curr_dir);
            print_char('\n');
            return (1);
        }
        print_string(get_env_var(info, "OLDPWD=")), print_char('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((new_dir = get_env_var(info, "OLDPWD=")) ? new_dir : "/");
    }
    else
        chdir_ret = chdir(info->argv_arr[1]);
    if (chdir_ret == -1)
    {
        print_error_message(info, "can't cd to ");
        write_str_to_fd(info->argv_arr[1], 2), print_error_char('\n');
    }
    else
    {
        add_env_var(info, "OLDPWD", get_env_var(info, "PWD="));
        add_env_var(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * display_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int display_help(info_t *info)
{
    char **arg_array;

    arg_array = info->argv_arr;
    print_string("help call works. Function not yet implemented \n");
    if (0)
        print_string(*arg_array); /* temp att_unused workaround */
    return (0);
}
