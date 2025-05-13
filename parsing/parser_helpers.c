#include "minishell.h"

/*
    this function creates a new IO node while parsing the command
    while the current token is a redirection operator proceed, remember the redirection
    get the next token, which should be filename/token
    if not a filename, set syntax error and return
    if correctly identifier is found then create a new IO node, and append it to the IO list
    consume the filename token
*/
bool ft_get_io_list(t_io_node **io_list)
{
    t_token_type redire_type;
    t_io_node *temp_io_node;

    if (g_minishell.parse_err.type)
        return false;
    while (g_minishell.curr_token && ft_is_redir(g_minishell.curr_token->type))
    {
        redire_type = g_minishell.curr_token->type;
        ft_get_next_token();
        if (!g_minishell.curr_token)
            return (ft_set_parse_err(E_SYNTAX), false);
        if (g_minishell.curr_token->type != T_IDENTIFIER)
            return (ft_set_parse_err(E_SYNTAX), false);
        temp_io_node = ft_new_io_node(redire_type, g_minishell.curr_token->value);
        if (!temp_io_node)
            return (ft_set_parse_err(E_MEM), false);
        ft_append_io_node(io_list, temp_io_node);
        ft_get_next_token();
    }
    return true;
}

/*
    the function accumulates consecutive identifier tokens onto one single string
    separated by spaces
    after the first argument, keep on appending the next identifier token
    until a non-identifier token is found
*/
bool ft_join_args(char **args)
{
    char *to_free;
    if (g_minishell.parse_err.type)
        return false;
    if (!*args) // if this is the first argument start from an empty string
        *args = ft_strdup("");
    if (!*args)
        return false;
    while (g_minishell.curr_token && g_minishell.curr_token->type == T_IDENTIFIER)
    {
        to_free = *args;
        *args = ft_strjoin_with(*args, g_minishell.curr_token->value, ' ');
        if (!*args)
            return (free(to_free), false);
        free(to_free);
        ft_get_next_token();
    }
    return true;
}

/*
    this funuction creates a command node of type N_CMD
    if the current token is an identifier, call ft_join_args to accumulate the args
    if the curr token is of redirection type, call ft_get_io_list to create the IO list
    return the populated t_node for the AST being created
*/
t_node *ft_get_simple_cmd(void)
{
    t_node *node;
    if (g_minishell.parse_err.type)
        return NULL;
    node = ft_new_node(N_CMD);
    if (!node)
        return (ft_set_parse_err(E_MEM), NULL);
    while (g_minishell.curr_token && (g_minishell.curr_token->type == T_IDENTIFIER || ft_is_redir(g_minishell.curr_token->type)))
    {
        if (g_minishell.curr_token->type == T_IDENTIFIER)
        {
            if (!ft_join_args(&(node->args)))
                return (ft_clear_cmd_node(node), ft_set_parse_err(E_MEM), NULL);
        }
        else if (ft_is_redir(g_minishell.curr_token->type))
        {
            if (!ft_get_io_list(&(node->io_list)))
                return (free(node->args), free(node), NULL);
        }
    }
    return node;
}