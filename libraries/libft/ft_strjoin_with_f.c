#include "libft.h"

// join two strings s1 and s2 with the char c in between them
// free the strings s1 and s2 and return the pointer to the joined string
char *ft_strjoin_with_f(char *s1, char *s2, char c)
{
    char *joined;
    size_t total_len, i, j;
    if (!s1 || !s2)
        return NULL;
    if (!c || !ft_strlen(s1) || !ft_strlen(s2))
        return ft_strjoin(s1, s2);
    total_len = ft_strlen(s1) + ft_strlen(s2) + 2;
    joined = ft_calloc(total_len, sizeof(char));
    if (!joined)
        return NULL;
    i = 0;
    while (s1[i])
    {
        joined[i] = s1[i];
        i++;
    }
    joined[i++] = c;
    j = 0;
    while (s2[j])
    {
        joined[i++] = s2[j];
        j++;
    }
    joined[i] = 0;
    return (free(s1), free(s2), joined);
}