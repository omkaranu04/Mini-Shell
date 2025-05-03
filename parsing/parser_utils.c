#include "minishell.h"

// advances to the next token in the global token list
void ft_get_next_token(void)
{
    g_minishell.curr_token = g_minishell.curr_token->next;
}

// check if the current token is a binary operator
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

// checks if a token is an IO redirection
bool ft_is_redir(t_token_type type)
{
    if (type == T_LESS || type == T_GREAT || type == T_DLESS || type == T_DGREAT)
        return true;
    return false;
}

// assigns the precedence level to operators for parsing order
int ft_prec(t_token_type type)
{
    if (type == T_OR || type == T_AND)
        return 0;
    return 1;
}

// returns the precedence level of the current token
int ft_curr_token_prec(void)
{
    return ft_prec(g_minishell.curr_token->type);
}