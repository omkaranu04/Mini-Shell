#include "libft.h"

size_t ft_strs_arr_len(char **strs)
{
    size_t i = 0;
    while (strs[i])
        i++;
    return i;
}