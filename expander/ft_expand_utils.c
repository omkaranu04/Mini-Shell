#include "minishell.h"

// checks if it is a valid shell variable name
bool ft_is_valid_var_char(char c)
{
    if (ft_isalnum(c) || c == '_')
        return true;
    return false;
}

// extracts the substring from curr position upto next quote or dollar
char *ft_handle_normal_str(char *str, size_t *i)
{
    size_t start = *i;
    while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
        (*i)++;
    return ft_substr(str, start, *i - start);
}

// extracts a substring inside double quotes, stopping at next " or $
static char *ft_handle_dquote_str(char *str, size_t *i)
{
    size_t start = *i;
    while (str[*i] != '"' && str[*i] != '$')
        (*i)++;
    return ft_substr(str, start, *i - start);
}

// extracts and returns the entire single quotes string, including the quotes
char *ft_handle_squotes(char *str, size_t *i)
{
    size_t start = *i;
    (*i)++;
    while (str[*i] != '\'')
        (*i)++;
    (*i)++;
    return ft_substr(str, start, *i - start);
}

// processes a double quotes string
char *ft_handle_dquotes(char *str, size_t *i)
{
    char *ret = ft_strdup("\"");
    (*i)++;
    while (str[*i] != '"')
    {
        if (str[*i] == '$')
            ret = ft_strjoin_f(ret, ft_handle_dollar(str, i));
        else
            ret = ft_strjoin_f(ret, ft_handle_dquote_str(str, i));
    }
    (*i)++;
    return ft_strjoin_f(ret, ft_strdup("\""));
}