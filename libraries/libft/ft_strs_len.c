#include "libft.h"

size_t ft_strs_len(char **str)
{
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}