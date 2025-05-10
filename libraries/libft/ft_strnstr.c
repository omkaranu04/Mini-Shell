#include "libft.h"

// helper function to compare two strings up to a specified length
// returns 1 if they are equal, 0 otherwise
static int ft_cmp(const char *s1, const char *s2, size_t len)
{
    size_t i = 0;
    while (i < len && s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    if (!s2[i])
        return 1;
    return 0;
}

// finds the first occurence of the string needle in the first len characters of the
// string haystack
char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t i = 0;
    if ((!haystack || !needle) && !len)
        return NULL;
    if (!ft_strlen(needle))
        return (char *)haystack;
    i = 0;
    while (haystack[i] && i < len)
    {
        if (haystack[i] == needle[0])
        {
            // if first character matches call the helper function
            if (ft_cmp(haystack + i, needle, len - i))
                return ((char *)(haystack + i));
        }
        i++;
    }
    return NULL;
}