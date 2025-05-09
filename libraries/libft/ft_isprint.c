#include "libft.h"

// returns if the character is a printable ascii character or not
// ' ' ascii 32 to '~' ascii 126 are printable characters
int ft_isprint(int c)
{
    if (c >= ' ' && c <= '~')
        return 1;
    return 0;
}