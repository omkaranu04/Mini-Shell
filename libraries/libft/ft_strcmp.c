#include "libft.h"

// function to compare two strings
// calls the ft_strncmp with the longer of the two strings
// returns 0 if they are equal, a positive number if s1 > s2,
// and a negative number if s1 < s2
int ft_strcmp(const char *s1, const char *s2)
{
    size_t s11 = ft_strlen(s1), s22 = ft_strlen(s2);
    if (s11 > s22)
        return ft_strncmp(s1, s2, s11);
    else
        return ft_strncmp(s1, s2, s22);
}