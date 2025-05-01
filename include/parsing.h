#ifndef PARSING_H
#define PARSING_H

#include "tokenizing.h"

// enum for types of nodes in AST
typedef enum e_node_type
{
    N_PIPE, // '\' operation node
    N_AND,  // && node
    N_OR,   // || node
    N_CMD   // simple command node
} t_node_type;

// enum for IO redirections
typedef enum e_io_type
{
    IO_IN,      // input redirection <
    IO_OUT,     // output redirection >
    IO_HEREDOC, // heredoc redirection <<
    IO_APPEND   // append redirection >>
} t_io_type;

// parsing error types
typedef enum e_parse_err_type
{
    E_MEM = 1, // memory allocation error
    E_SYNTAX   // syntax error
} t_parse_err_type;

// structure for redirection in a command
typedef struct s_io_node
{
    t_io_type type;                // kind of redirection from the enum type
    char *value;                   // file / delimiter string
    char **expanded_value;         // array of expanded strings (after variable expansion)
    int here_doc;                  // flag for heredoc handling
    struct s_io_node *prev, *next; // pointers for doubly linked list
} t_io_node;

// structure for node in a AST
typedef struct s_node
{
    t_node_type type;            // type of node as described above
    t_io_node *io_list;          // linked list of IO redirections for this command
    char *args;                  // raw commands as string
    char **expanded_args;        // after variable expansion
    struct s_node *left, *right; // tree structure left and right children
} t_node;

typedef struct s_parse_err
{
    t_parse_err_type type; // type of error as given above
    char *str;             // err msg or related thing
} t_parse_err;

// parser_clear.c
void ft_clear_io_list(t_io_node **lst);    // clear the IO list
void ft_clear_cmd_node(t_node *node);      // free a single cmd node
void ft_recursive_clear_ast(t_node *node); // recuresively free the AST
void ft_clear_ast(t_node **ast);           // free the entire AST

// parser_err.c
void ft_set_parse_err(t_parse_err_type type); // set the current parse error
void ft_handle_parse_err(void);               // handles or prints the parse error

// parser_helpers.c
bool ft_get_io_list(t_io_node **io_list); // parses and retrieves the IO redirections
bool ft_join_args(char **args);           // joins arguments
t_node *ft_get_simple_cmd(void);          // parses a simple cmd node

// parser_nodes.c
t_node_type ft_get_node_type(t_token_type type);                 // mpaps token type to node type
t_io_type ft_get_io_type(t_token_type type);                     // maps token type to IO type
t_node *ft_new_node(t_node_type type);                           // creates a new AST node
t_io_node *ft_new_io_node(t_token_type type, char *value);       // creates a new IO node
void ft_append_io_node(t_io_node **lst, t_io_node *new_io_node); // appends an io node ot the list

// parser_utils.c
void ft_get_next_token(void);        // get the next token
bool ft_curr_token_is_binop(void);   // check if curr token is bin op
bool ft_is_redir(t_token_type type); // check if the token is redirection
int ft_prec(t_token_type type);      // returns the precedence of the token
int ft_curr_token_prec(void);        // returns the precedence of the current token

// parser.c
t_node *ft_term(void);                                            // parse the terminal node
t_node *ft_combine(t_token_type op, t_node *left, t_node *right); // combine the two node with operation
t_node *ft_expression(int min_prec);                              // parses the expression with minimum precedence
t_node *ft_parse(void);                                           // builds an AST from the tokens

#endif