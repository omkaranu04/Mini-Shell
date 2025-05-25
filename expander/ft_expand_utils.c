#include "minishell.h"

/*
    returns true if the char is valid for a name in bash
*/
bool ft_is_valid_var_char(char c)
{
    if (ft_isalnum(c) || c == '_')
        return true;
    return false;
}

/* 
    returns the start till until either a single quote, duble quote, dollar or EOS is encountered
    returns the gathered chunk of the string
*/
char *ft_handle_normal_str(char *str, size_t *i)
{
    size_t start = *i;
    while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
        (*i)++;
    return ft_substr(str, start, *i - start);
}

/*
    called when inside a double quote and the next char
    is not a dollar sign,
    records the start and proceeds until another double quote or dollar sign is encountered
    copy the literal text inside the double quotes
*/
static char *ft_handle_dquote_str(char *str, size_t *i)
{
    size_t start = *i;
    while (str[*i] != '"' && str[*i] != '$')
        (*i)++;
    return ft_substr(str, start, *i - start);
}

/*
    returns the substring from the opening to the closing quote,
    preserving quotes and their content literally
*/
char *ft_handle_squotes(char *str, size_t *i)
{
    size_t start = *i;
    (*i)++;
    while (str[*i] != '\'')
        (*i)++;
    (*i)++;
    return ft_substr(str, start, *i - start);
}

/*
    str[*i] must be a double quote, begins by duplicating a leading " into ret and advancing the pointer
    loops until the closing double quote is found, if a dollar sign is encountered within, it calls 
    the function to expand the variable and concatenates the result
    o/w call the handler to grab the literal text and concatenate it
*/
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