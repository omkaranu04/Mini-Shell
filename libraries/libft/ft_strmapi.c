#include "libft.h"

// applt the function f to each character of the string s
// the modified string is returned
// unlike in striteri this function modifies a new string and returns it
// the original string is not modified
char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    char *new_str;
    size_t str_len, i;
    if (!s)
        return NULL;
    str_len = ft_strlen(s);
    new_str = ft_calloc(str_len + 1, sizeof(char));
    if (!new_str)
        return NULL;
    i = 0;
    while (s[i])
    {
        new_str[i] = f(i, s[i]);
        i++;
    }
    return new_str;
}