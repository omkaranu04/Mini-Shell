#include "minishell.h"

// function removes the empty quotes substrings from a string while preserving other content
char *ft_clean_empty_strs(char *str)
{
    size_t i, j, dstsize;
    char *temp, *ret;

    if ((str[0] == '\'' && str[1] == '\'' && !str[2]) || (str[0] == '"' && str[1] == '"' && !str[2]))
        return (str);
    temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
    i - 0, j = 0;
    while (str[i])
    {
        if ((str[i] == '\'' && str[i + 1] == '\'') || (str[i] == '"' && str[i + 1] == '"'))
            i += 2;
        else
            temp[j++] = str[i++];
    }
    free(str);
    dstsize = ft_strlen(temp) + 1;
    ret = ft_calloc(dstsize, sizeof(char));
    return (ft_strlcpy(ret, temp, dstsize), free(temp), ret);
}