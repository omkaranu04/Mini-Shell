#include "libft.h"

// char ***strs -> pointer to an array of string arrays
// returns the number of string arrays in the array
size_t ft_strs_arr_len(char ***strs)
{
    size_t i = 0;
    while (strs[i])
        i++;
    return i;
}