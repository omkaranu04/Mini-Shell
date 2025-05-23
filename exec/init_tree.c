#include "minishell.h"

// handling the ctrl+c signal in heredoc
static void ft_heredoc_sigint_handler(int signum)
{
    (void)signum;
    ft_clean_ms();
    exit(SIGINT);
}

// handles the heredoc input for a redirection node
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

// waits for the heredoc child process to finish
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

// initializes the leaf nodes of the AST
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

// initializes the AST
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