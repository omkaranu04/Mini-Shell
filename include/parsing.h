#ifndef PARSING_H
#define PARSING_H

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

#endif