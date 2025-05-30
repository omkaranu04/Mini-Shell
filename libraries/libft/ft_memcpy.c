#include "libft.h"

// copy the block of memory from src to dst of size n
// returns the pointer to the dst block
// does not handle memory overlaps
void *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t i = 0;
    while ((dst + i || src + i) && i < n)
    {
        ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
        i++;
    }
    return dst;
}