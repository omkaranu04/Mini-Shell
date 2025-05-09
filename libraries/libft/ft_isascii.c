#include "libft.h"

// checks if the int param c is representing an valid ascii character
int ft_isascii(int c)
{
    if (c >= 0 && c <= 127)
        return 1;
    return 0;
}