#ifndef PARSING_H
#define PARSING_H

/*
    The library for the parser phase of the minishell
    Here we will focus mainly on building the AST (Abstract Syntax Tree)
    The parser will take the tokenized input and build a tree structure
*/

#include "tokenizing.h"

/*
    Defines the types of nodes in the AST
    N_PIPE  -> | operator, connects two commands
    N_AND   -> && operator, logical AND
    N_OR    -> || operator, logical OR
    N_CMD   -> simple command with args
*/
typedef enum e_node_type
{
    N_PIPE,
    N_AND,
    N_OR,
    N_CMD
} t_node_type;

/*
    Defines the types of I/O redirections
    IO_IN      -> < operator, input redirection
    IO_OUT     -> > operator, output redirection
    IO_HEREDOC -> << operator, here document
    IO_APPEND  -> >> operator, append output redirection
*/
typedef enum e_io_type
{
    IO_IN,
    IO_OUT,
    IO_HEREDOC,
    IO_APPEND
} t_io_type;

/*
    Defines the types of parsing errors
    E_MEM    -> memory allocation error
    E_SYNTAX -> syntax error in cmd
*/
typedef enum e_parse_err_type
{
    E_MEM = 1,
    E_SYNTAX
} t_parse_err_type;

/*
    This represents an IO redirection node 
    t_io_type type                  -> type of redirection
    char *value                     -> filename/delimiter string
    char **expanded_value           -> filename after expansion
    int here_doc                    -> a fd for heredoc
    struct s_io_node *prev, *next   -> for DLL of IO redirections
*/
typedef struct s_io_node
{
    t_io_type type;
    char *value;
    char **expanded_value;
    int here_doc;
    struct s_io_node *prev, *next;
} t_io_node;

/*
    This represents a node in AST
    t_node_type type            -> type of node from t_node_type
    t_io_node *io_list          -> a LL of IO redirections associated with this command
    char *args                  -> cmd args as string
    char **expanded_args        -> cmd args after variable expansion
    struct s_node *left, *right -> pointers to child nodes (for operators like pipe, AND, OR)
*/
typedef struct s_node
{
    t_node_type type;
    t_io_node *io_list;
    char *args;
    char **expanded_args;
    struct s_node *left, *right;
} t_node;

/*
    This represents a parsing error
    t_parse_err_type type       -> type of error from t_parse_err_type
    char *str                   -> error message string
*/
typedef struct s_parse_err
{
    t_parse_err_type type;
    char *str;
} t_parse_err;

// parser_clear.c
void ft_clear_io_list(t_io_node **lst);
void ft_clear_cmd_node(t_node *node);
void ft_recursive_clear_ast(t_node *node);
void ft_clear_ast(t_node **ast);

// parser_err.c
void ft_set_parse_err(t_parse_err_type type);
void ft_handle_parse_err(void);

// parser_helpers.c
bool ft_get_io_list(t_io_node **io_list);
bool ft_join_args(char **args);
t_node *ft_get_simple_cmd(void);

// parser_nodes.c
t_node_type ft_get_node_type(t_token_type type);
t_io_type ft_get_io_type(t_token_type type);
t_node *ft_new_node(t_node_type type);
t_io_node *ft_new_io_node(t_token_type type, char *value);
void ft_append_io_node(t_io_node **lst, t_io_node *new);

// parser_utils.c
void ft_get_next_token(void);
bool ft_curr_token_is_binop(void);
bool ft_is_redir(t_token_type type);
int ft_prec(t_token_type type);
int ft_curr_token_prec(void);

// parser.c
t_node *ft_term(void);
t_node *ft_combine(t_token_type op, t_node *left, t_node *right);
t_node *ft_expression(int min_prec);
t_node *ft_parse(void);

#endif