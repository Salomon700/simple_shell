#include "shell.h"

/**
 *print_error_str - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_error_str(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        print_error_char(str[i]);
        i++;
    }
}

/**
 * print_error_char - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_error_char(char c)
{
    static int i;
    static char buf[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUFFER_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * write_to_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_to_fd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUFFER_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 *write_str_to_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int write_str_to_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += write_to_fd(*str++, fd);
    }
    return (i);
}
