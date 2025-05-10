#include "minishell.h"

/*
    the function adds a separator token to the token list
    advances the line pointer move past the separator
    returns 1 on success, 0 on failure
*/
int ft_append_separator(t_token_type type, char **line_ptr, t_token **token_list)
{
    t_token *token;
    token = ft_new_token(NULL, type);
    if (!token)
        return 0;
    ft_token_list_add_back(token_list, token);
    (*line_ptr)++;

    // if double separator, move past the second char
    if (type == T_DLESS || type == T_DGREAT || type == T_OR || type == T_AND)
        (*line_ptr)++;
    return 1;
}

/*
    function handles the creation of the identifier tokens
    identifies the length of the identifier till it finds a separator
    if a quote is found, it skips over the quote 
    once the length of the identifier is known it is extracted using the ft_substr function
    and the identifier is inserted in the token list and the line ptr advances to the end of identifier
*/
int ft_append_identifier(char **line_ptr, t_token **token_list)
{
    char *tmp_line, *value;
    t_token *token;
    size_t i = 0;
    tmp_line = *line_ptr;
    while (tmp_line[i] && !ft_is_separator(tmp_line + i))
    {
        if (ft_is_quote(tmp_line[i]))
        {
            if (!ft_skip_quotes(tmp_line, &i))
                return (ft_print_quote_err(tmp_line[i]), 0);
        }
        else
            i++;
    }
    value = ft_substr(tmp_line, 0, i);
    if (!value)
        return 0;
    token = ft_new_token(value, T_IDENTIFIER);
    if (!token)
        return (free(value), 0);
    *line_ptr += i;
    return (ft_token_list_add_back(token_list, token), 1);
}