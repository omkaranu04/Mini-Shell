#include "libft.h"

char *ft_strchr(const char *s, int c)
{
    size_t i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)(s + i));
        i++;
    }
    if (!(char)c)
        return ((char *)(s + i));
    else
        return NULL;
}