#include "libft.h"

// writes a character to the specified fd
// the laast param 1 in the write refers to the size of data to be written
void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}