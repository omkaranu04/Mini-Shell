#include "minishell.h"

/*
    the function handles shell operators and special syntax elements
    it does a series of conditional checks to identify which token is present
    at the current position in the line
    for each case it calls the ft_append_separator func
*/
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

/*
    this function is the main tokenization controller
    it iterates over each char of the line until it reaches the end
        - If the current character is whitespace, it skips all consecutive whitespace using ft_skip_spaces
        - If the current character is a separator, it calls ft_handle_separator to handle it
        - Otherwise, it assumes the current position is the start of an identifier and calls ft_append_identifier
        - it sets the error flag if either of the function call fails

    finally returns the token list
*/
t_token *ft_tokenization_handler(char *line)
{
    int err;
    t_token *token_list;
    err = 0;
    token_list = NULL;
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