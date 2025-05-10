#include "libft.h"

// copy a string to a new allocated memory block and 
// return a pointer to it
char *ft_strdup(const char *s1)
{
    char *s2;
    size_t s11;
    s11 = ft_strlen(s1);
    s2 = ft_calloc(s11 + 1, sizeof(char));
    if (!s2)
        return NULL;
    return ft_memcpy(s2, s1, s11);
}