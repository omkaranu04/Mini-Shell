#include "libft.h"

// sets the first n bytes of the memory pointed by s to NULL
void ft_bzero(void *s, size_t n)
{
    size_t i = 0;
    while (i < n)
    {
        ((unsigned char *)s)[i] = 0;
        i++;
    }
}