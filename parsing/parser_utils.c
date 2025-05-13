#include "minishell.h"

// moves the parser's current token pointer to the next token in the list
void ft_get_next_token(void)
{
    g_minishell.curr_token = g_minishell.curr_token->next;
}

/*
    returns true if the current token type is of a binary operator
    (|, &&, ||) then true, false otherwise
*/
bool ft_curr_token_is_binop(void)
{
    t_token_type type;
    if (!g_minishell.curr_token)
        return false;
    type = g_minishell.curr_token->type;
    if (type == T_PIPE || type == T_AND || type == T_OR)
        return true;
    return false;
}

/*
    returns true if the current token type is of redirection one
    (<, >, <<, >>) then true, false otherwise
*/
bool ft_is_redir(t_token_type type)
{
    if (type == T_LESS || type == T_GREAT || type == T_DLESS || type == T_DGREAT)
        return true;
    return false;
}

/*
    assigns a numeric precedence to logical operators
    lower numbers mean lower binding power, i.e. higher precedence
*/
int ft_prec(t_token_type type)
{
    if (type == T_OR || type == T_AND)
        return 0;
    return 1;
}

/*
    returns the precedence of the current token
*/
int ft_curr_token_prec(void)
{
    return ft_prec(g_minishell.curr_token->type);
}