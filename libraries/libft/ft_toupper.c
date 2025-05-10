#include "libft.h"

// convert the char given to upper case
int ft_toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - ('a' - 'A'));
    return c;
}