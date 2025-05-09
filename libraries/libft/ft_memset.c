#include "libft.h"

// sets the first len bytes of the mmeory block pointed by b to the value specified by c
// c -> taken as int but treated as unsigned char
void *ft_memset(void *b, int c, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        ((unsigned char *)b)[i] = (unsigned char)c;
        i++;
    }
    return b;
}