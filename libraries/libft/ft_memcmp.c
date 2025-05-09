#include "libft.h"

// returns 0 if the two memory  blocks are same till the specified byte
// all are treated as unsigned char, if difference is found then the difference between two
// bytes is returned
// if +ve returned then s1 > s2, else s1 < s2
int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    size_t i = 0;
    while (i < n)
    {
        if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
            return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
        i++;
    }
    return 0;
}