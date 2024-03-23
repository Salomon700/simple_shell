#include "shell.h"

/**
 * is_interactive_mode - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive_mode(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd_val <= 2);
}

/**
 * is_delim_char - checks if character is a delimeter
 * @c: the char to check
 * @delim_str: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim_char(char c, char *delim_str)
{
    while (*delim_str)
        if (*delim_str++ == c)
            return (1);
    return (0);
}

/**
 *is_alpha_char - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha_char(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 *convert_to_int - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int convert_to_int(char *str)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0;  str[i] != '\0' && flag != 2; i++)
    {
        if (str[i] == '-')
            sign *= -1;

        if (str[i] >= '0' && str[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (str[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output);
}
