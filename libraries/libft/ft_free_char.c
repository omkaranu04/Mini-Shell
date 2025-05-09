#include "libft.h"

// frees an array of strings
void ft_free_char2(char **tofree)
{
    size_t i;
    if (!tofree)
        return;
    i = 0;
    while (tofree[i])
        free(tofree[i++]);
    free(tofree);
}

// frees an array of arrays of strings
void ft_free_char3(char ***tofree)
{
    size_t i;
    if (!tofree)
        return;
    i = 0;
    while (tofree[i])
        ft_free_char2(tofree[i++]);
    free(tofree);
}