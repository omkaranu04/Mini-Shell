#include "minishell.h"

/*
    serves as the call for the main tokenizer function
    it takes the line from the g_minishell struct, processes it using the function
    sets the g_minishell.line to NULL to tell that the line has been processed
    returns the generated token list by the tokenizer
*/
t_token *ft_tokenize(void)
{
    char *line;
    t_token *token_list;
    line = g_minishell.line;
    token_list = ft_tokenization_handler(line);
    free(line);
    g_minishell.line = NULL;
    return token_list;
}