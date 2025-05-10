#include "libft.h"

// compares at most n characters from two strings
// returns 0 if they are equal, a positive number if s1 > s2, 
// and a negative number if s1 < s2
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    if (n)
    {
        while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
            i++;
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    }
    return 0;
}