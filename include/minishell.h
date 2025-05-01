#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <termios.h>
#include <limits.h>
#include "libft.h"
#include "tokenizing.h"
#include "parsing.h"

// linked list for environment variables
typedef struct s_env
{
    char *key, *value;
    struct s_env *next;
} t_env;

// enum for error handling
typedef enum e_err_msg
{
    ERRMSG_CMB_NOT_FOUND,
    ERRMSG_NO_SUCH_FILE,
    ERRMSG_PERM_DENIED,
    ERRMSG_AMBIGUOUS,
    ERRMSG_TOO_MANY_ARGS,
    ERRMSG_NUMERIC_REQUI
} t_err_msg;

// enumerate error codes, matching standard shell exit codes
typedef enum e_err_no
{
    ENO_SUCCESS,
    ENO_GENERAL,
    ENO_CANT_EXEC = 126,
    ENO_NOT_FOUND,
    ENO_EXEC_255 = 255
} t_err_no;

// AST (Abstract Syntax Tree) direction
typedef enum e_ast_direction
{
    TD_LEFT,
    TD_RIGHT
} t_ast_direction;

// structure for error handling
typedef struct s_err
{
    t_err_no no;
    t_err_msg msg;
    char *cause;
} t_err;

// structure to hold the resolved path and the errors within resolution
typedef struct s_path
{
    t_err err;
    char *path;
} t_path;

// main shell state structure
typedef struct s_minishell
{
    char *line;                   // curr input line
    t_token *tokens, *curr_token; // tokenized input, curr token being processed
    t_node *ast;                  // AST for the command
    int exit_s;                   // last exit status
    bool sigint_child;            // catch the Ctrl+C signal
    t_parse_err parse_err;        // parsing error check
    int stdin, stdout;            // FDs for stdin, stdout
    char **environ;               // environment variables array
    t_env *envlst;                // linked list of evironment variables
    bool heredoc_sigint;          // SIGINT received during the 'heredoc'
    struct termios original_term; // original terminal attributes
} t_minishell;

#endif