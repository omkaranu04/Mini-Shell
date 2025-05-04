#include "minishell.h"

// handles the shell operators and syntax elements
int ft_handle_separator(char **line_ptr, t_token **token_list)
{
    if (!ft_strncmp(*line_ptr, "<<", 2))
        return (ft_append_separator(T_DLESS, line_ptr, token_list) && 1);
    else if (!ft_strncmp(*line_ptr, ">>", 2))
        return (ft_append_separator(T_DGREAT, line_ptr, token_list) && 1);
    else if (!ft_strncmp(*line_ptr, "<", 1))
        return (ft_append_separator(T_LESS, line_ptr, token_list) && 1);
    else if (!ft_strncmp(*line_ptr, ">", 1))
        return (ft_append_separator(T_GREAT, line_ptr, token_list) && 1);
    else if (!ft_strncmp(*line_ptr, "(", 1))
        return (ft_append_separator(T_O_PARENT, line_ptr, token_list) && 1);
    else if (!ft_strncmp(*line_ptr, ")", 1))
        return (ft_append_separator(T_C_PARENT, line_ptr, token_list) && 1);
    else if (!ft_strncmp(*line_ptr, "&&", 2))
        return (ft_append_separator(T_AND, line_ptr, token_list) && 1);
    else if (!ft_strncmp(*line_ptr, "||", 2))
        return (ft_append_separator(T_OR, line_ptr, token_list) && 1);
    else
        return (ft_append_separator(T_PIPE, line_ptr, token_list) && 1);
}

// initializes the token list
t_token *ft_tokenization_handler(char *line)
{
    int err;
    t_token *token_list;
    while (*line)
    {
        if (err)
            return (ft_clear_token_list(&token_list), NULL);
        if (ft_isspace(*line))
            ft_skip_spaces(&line);
        else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1) || !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2) || !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
            err = (!ft_handle_separator(&line, &token_list) && 1);
        else
            err = (!ft_append_identifier(&line, &token_list) && 1);
    }
    return token_list;
}