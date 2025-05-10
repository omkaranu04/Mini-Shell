#include "libft.h"

// return the substring specified from the start index to the specified length
// return the pointer to the new substring formed
char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *substr;
    size_t i, slen;
    if (!s)
        return NULL;
    slen = ft_strlen(s);
    if (!slen || start > slen - 1)
        return ft_strdup("");
    i = 0;
    while (s[start + 1] && i + 1 <= len)
        i++;
    substr = ft_calloc(i + 1, sizeof(char));
    if (!substr)
        return NULL;
    i = 0;
    while (i < len && s[start + i])
    {
        substr[i] = s[start + i];
        i++;
    }
    return substr;
}