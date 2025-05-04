#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <termios.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
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
    ERRMSG_CMD_NOT_FOUND,
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

extern t_minishell g_minishell;

// ----- BUILTINS ----- //
// cd.c
int ft_cd(char *path); // change directory

// echo.c
int ft_echo(char **args); // prints args to stdout

// env_utils.c
char *ft_get_envlst_val(char *key);                        // get value by key
bool ft_env_entry_exists(char *key);                        // check if key exists
void ft_update_envlst(char *key, char *value, bool create); // update or create entry

// env.c
// functions for extracting keys/values and initializing the env list
char *ft_extract_key(char *str);
char *ft_extract_value(char *str);
void ft_init_envlst(void);
int ft_env(void);

// exit.c
void ft_exit(char **args); // exits the shell

// export.c
int ft_check_key(char *str); // validate export key
int ft_export(char **args);  // export variables

// pwd.c
int ft_pwd(void); // prints the current working directory

// unset.c
int ft_unset(char **args); // unset the env variables

// ----- CLEANING ----- //
// ft_clean_ms.c
void ft_clean_ms(void); // cleans up the shell state and resources

// ----- EXEC ----- //
// error_msg.c
int ft_err_msg(t_err err); // prints/handles error messages

// exec_builtin.c
int ft_exec_builtin(char **args); // executes the builtin commands
bool ft_is_builtin(char *arg);    // checks if the command is a builtin

// exec_redirect.c
int ft_out(t_io_node *io_list, int *status);    // output redirection
int ft_in(t_io_node *io_list, int *status);     // input redirection
int ft_append(t_io_node *io_list, int *status); // append redirection

// exec_utils.c
void *ft_garbage_collector(void *ptr, bool clean); // garbage collector
bool ft_is_delimiter(char *delimiter, char *str);  // check if str is a delimiter

// exec.c
int ft_get_exit_status(int status);         // gets the exit status of a child process
int ft_exec_node(t_node *tree, bool piped); // executes the command node

// exist_check.c
t_err ft_check_exec(char *file, bool cmd); // checks if the file is executable
t_err ft_check_read(char *file);           // checks if the file is readable
t_err ft_check_write(char *file);          // checks if the file is writable

// ft_exec_simple_cmd.c
int ft_check_redirection(t_node *node);           // checks for redirection
void ft_reset_stds(bool piped);                   // resets the stdin and stdout
int ft_exec_simple_cmd(t_node *node, bool piped); // executes a simple command

// ft_get_path.c
t_path ft_get_path(char *cmd); // resolves the path for command

// init_tree.c
void ft_init_tree(t_node *node);          // initializes the AST
void ft_heredoc(t_io_node *io, int p[2]); // handles heredoc

// ----- EXPANDER ----- //
// ft_asterisker.c
bool ft_match_star(char *pattern, char *str); // matches pattern with *

// ft_clean_empty_strs.c
char *ft_clean_empty_strs(char *str); // removes empty strings

// ft_exapnd_utils.c
bool ft_is_valid_var_char(char c);                // checks if char is a valid in var name
char *ft_handle_normal_str(char *str, size_t *i); // handles normal strings during expansion
char *ft_handle_squotes(char *str, size_t *i);    // handles single quoted strings
char *ft_handle_dquotes(char *str, size_t *i);    // handles double quoted strings

// ft_expand.c
char *ft_handle_dollar(char *str, size_t *i); // handles var expansion
char **ft_expand(char *str);                  // expands the input string

// ft_expander_split.c
char **ft_expander_split(char const *s); // splits the expanded string

// ft_globber_utils.c
bool ft_contains_asterisk(char *str);      // checks if str contains *
size_t ft_str_arr_len(char **str_arr);     // length of the string array
size_t ft_match_count(char *pattern);      // counts the matches for a pattern
char **ft_join_str_arrs(char ***str_arrs); //  joins the arrays of strings

// ft_globber.c
char **ft_globber(char **expanded); // handles globbing

// ft_strip_quotes.c
char *ft_strip_quotes(char *str); // remvies quotes from the string

// heredoc_expander.c
void ft_heredoc_expander(char *str, int fd); // expands the variables in the heredoc input

// ----- MINISHELL ----- //
// main_signals.c
void ft_sigquit_handler(int num); // handles the SIGQUIT signal
void ft_init_signals(void);       // initializes the signal handlers

#endif