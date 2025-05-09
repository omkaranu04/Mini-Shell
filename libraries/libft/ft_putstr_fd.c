#include "libft.h"

// writes a string to the specified fd, char by char using the
// ft_putchar_fd function
void ft_putstr_fd(char *s, int fd)
{
    if (s)
    {
        while (*s)
            ft_putchar_fd(*s++, fd);
    }
}