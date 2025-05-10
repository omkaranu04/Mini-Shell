#include "libft.h"

// char **str -> pointer to the array of strings
// returns the number of strings in the array
size_t ft_strs_len(char **str)
{
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}