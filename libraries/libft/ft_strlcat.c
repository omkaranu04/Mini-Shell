#include "libft.h"

// concateate the string src to the end of string dst, whila always maintaining the 
// NULL termination for safety
// truncation is detetcted if the return val >= dstsize
size_t ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t dst_len, i, j;
    if ((!dst || !src) && !dstsize)
    {
        if (dst)
            return ft_strlen(dst);
        return ft_strlen(src);
    }
    dst_len = ft_strlen(dst);
    if (dstsize <= dst_len)
        return dstsize + ft_strlen(src);
    i = 0;
    while (dst[i])
        i++;
    j = 0;
    while (src[j] && i < (dstsize - 1))
        dst[i++] = src[j++];
    dst[i] = 0;
    return dst_len + ft_strlen(src);
}