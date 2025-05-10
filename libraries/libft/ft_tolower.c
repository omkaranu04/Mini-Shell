#include "libft.h"

// convert the char given to lower case
int ft_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + ('a' - 'A'));
    return c;
}