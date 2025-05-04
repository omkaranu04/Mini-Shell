#ifndef TOKENIZING_H
#define TOKENIZING_H

#include <stdio.h>
#include <stdint.h>

#define PROMPT "minishell$ "

// cover all shell syntax elements in the enum type
typedef enum e_token_type
{
    T_IDENTIFIER, // generic argument e.g. "ls"
    T_LESS,       // input redirection
    T_GREAT,      // output redirection
    T_DLESS,      // heredoc
    T_DGREAT,     // append redirection
    T_PIPE,       // '|'
    T_O_PARENT,   // '('
    T_C_PARENT,   // ')'
    T_AND,        // '&&'
    T_OR,         // '||'
    T_NL,         // newline
} t_token_type;

// struct to depict a token in the doubly linked list
typedef struct s_token
{
    t_token_type type;    // type of token from enum
    char *value;          // value of token
    struct s_token *next; // next token in linked list
    struct s_token *prev; // previous token in linked list
} t_token;

// tokenizer_appenders.c
int ft_append_separator(t_token_type type, char **line_ptr, t_token **token_list); // adds syntax tokens like '>', '|' to the list
int ft_append_identifier(char **line_ptr, t_token **token_list);                   // extracts command tokens

// tokenizer_handlers.c
int ft_handle_separator(char **line_ptr, t_token **token_list); // process syntax chars
t_token *ft_tokenization_handler(char *line);                   // main tokenization entry point

// tokenizer_lst.c
t_token *ft_new_token(char *value, t_token_type type);          // create a new token
void ft_token_list_add_back(t_token **lst, t_token *new_token); // add a token in the list
void ft_clear_token_list(t_token **lst);                        // frees the token list

// tokenizer_utils.c
int ft_is_quote(char c);                    // check if the chart is a quote
int ft_is_separator(char *s);               // check is the char is a separator
void ft_skip_spaces(char **line);           // skip all the whitespaces
bool ft_skip_quotes(char *line, size_t *i); // skips the quoted regions
void ft_print_quote_err(char c);            // prints the unclosed quote errors

// tokenizer.c
t_token *ft_tokenize(void); // converts the input line to a token list

#endif