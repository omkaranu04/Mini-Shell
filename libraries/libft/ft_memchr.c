#include "libft.h"

// searches for the first occurence of a specific byte value within a memory block till specified size
// s -> pointer to memory block, c -> byte value to be searched (taken as int but treated as unsigned char)
// n -> size of block till where we need to search
// returns the pointer to that specified occurence or NULL
void *ft_memchr(const void *s, int c, size_t n)
{
    size_t i = 0;
    while (i < n)
    {
        if ((unsigned char)c == ((unsigned char *)s)[i])
            return ((void *)(s + i));
        i++;
    }
    return NULL;
}