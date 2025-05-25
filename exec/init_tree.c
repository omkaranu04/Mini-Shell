#include "minishell.h"

/*
    the function is a signal handler for the sigint during the heredoc input
    it calls the ft_clean_ms to clean up all the minishell resources
    and exits with SIGINT
*/
static void ft_heredoc_sigint_handler(int signum)
{
    (void)signum;
    ft_clean_ms();
    exit(SIGINT);
}

/*
    the funtion handles the collection of heredoc input
    it checks if the delimiter contains quotes by searching for them
    it reads the lines from the user with a '>' prompt
    if the line matches the delimiter, it breaks the loop
    if delimiter has no quotes then it expands the line
    then each line is written to the pipe
    finally it cleans up the minishell resources and exits with 0
*/
void ft_heredoc(t_io_node *io, int p[2])
{
    char *line, *quotes;
    signal(SIGINT, ft_heredoc_sigint_handler);
    quotes = io->value;
    while (*quotes && *quotes != '"' && *quotes != '\'')
        quotes++;
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_is_delimiter(io->value, line))
            break;
        if (!*quotes)
            ft_heredoc_expander(line, p[1]);
        else
        {
            ft_putstr_fd(line, p[1]);
            ft_putstr_fd("\n", p[1]);
        }
    }
    ft_clean_ms();
    exit(0);
}

/*
    function handles the parent process's tasks after the heredoc child process
    waits for the heredoc child, sets up the SIGQUIT handler
    resets the sigint flag, closes the write end of the pipe
    checks if the child exited with SIGINT, if so returns true
*/
static bool ft_leave_leaf(int p[2], int *pid)
{
    waitpid(*pid, pid, 0);
    signal(SIGQUIT, ft_sigquit_handler);
    g_minishell.sigint_child = false;
    close(p[1]);
    if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
        return true;
    return false;
}

/*
    the function initializes a leaf node in AST
    if the node has arguments it expands them, it iterates through the redirection of the node
    if the redirection is of heredoc, it does required setup for that
    for others it just expands the filename/value
*/
static void ft_init_leaf(t_node *node)
{
    t_io_node *io;
    int p[2], pid;
    if (node->args)
        node->expanded_args = ft_expand(node->args);
    io = node->io_list;
    while (io)
    {
        if (io->type == IO_HEREDOC)
        {
            pipe(p);
            g_minishell.sigint_child = true;
            pid = (signal(SIGINT, SIG_IGN), fork());
            if (!pid)
                ft_heredoc(io, p);
            if (ft_leave_leaf(p, &pid))
                return;
            io->here_doc = p[0];
        }
        else
            io->expanded_value = ft_expand(io->value);
        io = io->next;
    }
}

/*
    the maain function to initialize the entire AST
    if the node is NULL returns immediately
    if node is an operator then recursively initialize the left subtree
    if no heredoc was interuppted it initializes the right subtree
*/
void ft_init_tree(t_node *node)
{
    if (!node)
        return;
    if (node->type == N_PIPE || node->type == N_AND || node->type == N_OR)
    {
        ft_init_tree(node->left);
        if (!g_minishell.heredoc_sigint)
            ft_init_tree(node->right);
    }
    else
        ft_init_leaf(node);
}