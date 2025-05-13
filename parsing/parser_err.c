#include "minishell.h"

// simply sets the global parsing error type to the given type
void ft_set_parse_err(t_parse_err_type type)
{
    g_minishell.parse_err.type = type;
}

/*
    checks the global error type set in g_minishell
    if it is a syntax error, then print the error message, and set exit status to 258
    regardless of the error type, clear the AST and the token list
*/
void ft_handle_parse_err(void)
{
    t_parse_err_type type;
    t_token_type token_type;
    char **types;
    types = (char *[]){"T_IDENTIFIER",
                       "<", ">", "<<", ">>", "|", "(", ")", "&&", "||", "newline"};
    type = g_minishell.parse_err.type;
    (void)token_type;
    (void)types;
    if (type)
    {
        if (type == E_SYNTAX)
        {
            if (!g_minishell.curr_token) // determmine which token triggered the error
                token_type = T_NL;
            else
                token_type = g_minishell.curr_token->type;
            ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
            ft_putstr_fd(types[token_type], 2);
            ft_putstr_fd("'\n", 2);
            g_minishell.exit_s = 258;
        }
        ft_clear_ast(&g_minishell.ast);
        ft_bzero(&g_minishell.parse_err, sizeof(t_parse_err));
    }
}