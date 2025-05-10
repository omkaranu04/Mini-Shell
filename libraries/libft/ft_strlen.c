#include "libft.h"

// returns the length of the string exclusing the NULL termination
size_t ft_strlen(const char *str)
{
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}