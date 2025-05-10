#include "libft.h"

// copies a string from src to dst, while always maintaining 
// the NULL termination for safety
// truncation is detected if the return val >= dstsize
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i = 0;
    if (dstsize)
    {
        while (i < dstsize - 1 && src[i])
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = 0;
    }
    return ft_strlen(src);
}