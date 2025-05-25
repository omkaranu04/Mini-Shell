#include "minishell.h"

/*
    calculates how many characters the string will have after all the quotes are
    stripped off
*/
static size_t ft_unquoted_strlen(char *str)
{
    size_t i = 0, len = 0;
    char quotes = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            if (!quotes)
                quotes = str[i++];
            else if (str[i] == quotes)
                quotes = ((i++) && 0);
            else
                len += (i++ || 1);
        }
        else
            len += (i++ || 1);
    }
    return len;
}

/*
    copies one quoted segment from the source to the dest buffer
    omitting the surrounding quotes
*/
static void ft_unquote_filler(char *str, size_t *i, char *ret, size_t *j)
{
    char quotes = str[(*i)++];
    while (str[*i] != quotes)
        ret[(*j)++] = str[(*i)++];
    (*i)++;
}

/*
    builds and returns the full unquoted string
*/
char *ft_strip_quotes(char *str)
{
    char *ret = ft_calloc(1 + ft_unquoted_strlen(str), sizeof(char));
    size_t i = 0, j = 0;
    if (!ret)
        return NULL;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            ft_unquote_filler(str, &i, ret, &j);
        else
            ret[j++] = str[i++];
    }
    return (free(str), ret);
}