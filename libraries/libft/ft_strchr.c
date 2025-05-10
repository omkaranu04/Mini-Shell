#include "libft.h"

// returns the pointer to the first occurrence of the char c
// in the string s; if c is not found, returns NULL
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