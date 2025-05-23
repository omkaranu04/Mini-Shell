#include "libft.h"

// joins the two strings s1 and s2 into a new string and then frees the two 
// strings s1 and s2
// returns the pointer to the new string
char *ft_strjoin_f(char *s1, char *s2)
{
    char *joined;
    size_t total_len, i, j;
    if (!s1 || !s2)
        return NULL;
    total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
    joined = ft_calloc(total_len, sizeof(char));
    if (!joined)
        return NULL;
    i = 0;
    while (s1[i])
    {
        joined[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        joined[i++] = s2[j];
        j++;
    }
    joined[i] = 0;
    return (free(s1), free(s2), joined);
}