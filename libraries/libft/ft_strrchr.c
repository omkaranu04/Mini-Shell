#include "libft.h"

// searches the last occurence of the specific char c in the string s
// returns a pointer to the last occurence of c in s
char *ft_strrchr(const char *s, int c)
{
    size_t slen = ft_strlen(s);
    if (!(char)c)
        return ((char *)(s + slen));
    while (slen--)
    {
        if (s[slen] == (char)c)
            return ((char *)(s + slen));
    }
    return NULL;
}