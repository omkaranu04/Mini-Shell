#ifndef TOKENIZING_H
#define TOKENIZING_H

#include <stdio.h>
#include <stdint.h>

#define PROMPT "minishell$ "

/*
    T_IDENTIFIER    ->  cmd anmes, args, or other text
    T_LESS          -> < (input redirection)
    T_GREAT         -> > (output redirection)
    T_DLESS         -> << (here-doc redirection)
    T_DGREAT        -> >> (append redirection)
    T_PIPE          -> | (pipe)
    T_O_PARENT      -> ( (open parenthesis)
    T_C_PARENT      -> ) (close parenthesis)
    T_AND           -> && (logical AND)
    T_OR            -> || (logical OR)
    T_NL            -> \n (newline token)
*/
typedef enum e_token_type
{
    T_IDENTIFIER,
    T_LESS,
    T_GREAT,
    T_DLESS,
    T_DGREAT,
    T_PIPE,
    T_O_PARENT,
    T_C_PARENT,
    T_AND,
    T_OR,
    T_NL,
} t_token_type;

/*
    The structure represents a single token in the token list
    implemented as a doubly linked list.
    t_token_type type       -> token type from the enum above
    char *value             -> actual string content of the token
    struct s_token *next    -> next pointer of DLL
    struct s_token *prev    -> prev pointer of DLL
*/
typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
    struct s_token *prev;
} t_token;

// tokenizer_appenders.c
int ft_append_separator(t_token_type type, char **line_ptr, t_token **token_list);
int ft_append_identifier(char **line_ptr, t_token **token_list);

// tokenizer_handlers.c
int ft_handle_separator(char **line_ptr, t_token **token_list);
t_token *ft_tokenization_handler(char *line);

// tokenizer_lst.c
t_token *ft_new_token(char *value, t_token_type type);
void ft_token_list_add_back(t_token **lst, t_token *new_token);
void ft_clear_token_list(t_token **lst);

// tokenizer_utils.c
int ft_is_quote(char c);
int ft_is_separator(char *s);
void ft_skip_spaces(char **line);
bool ft_skip_quotes(char *line, size_t *i);
void ft_print_quote_err(char c);

// tokenizer.c
t_token *ft_tokenize(void);

#endif