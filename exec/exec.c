#include "minishell.h"

// depending on the direction, it will execute the left or right node
static void ft_exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction)
{
    int status;
    if (direction == TD_LEFT)
    {
        close(pfds[0]);
        dup2(pfds[1], STDOUT_FILENO);
        close(pfds[1]);
    }
    else if (direction == TD_RIGHT)
    {
        close(pfds[1]);
        dup2(pfds[0], STDIN_FILENO);
        close(pfds[0]);
    }
    status = ft_exec_node(node, true);
    (ft_clean_ms(), exit(status));
}

// gets the exit status of a child process
int ft_get_exit_status(int status)
{
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (WEXITSTATUS(status));
}

// creates a pipe, forks the process, and executes the left and right nodes
static int ft_exec_pipeline(t_node *tree)
{
    int status, pfds[2], pidl, pidr;
    g_minishell.sigint_child = true;
    pipe(pfds);
    pidl = fork();
    if (!pidl)
        ft_exec_pipe_child(tree->left, pfds, TD_LEFT);
    else
    {
        pidr = fork();
        if (!pidr)
            ft_exec_pipe_child(tree->right, pfds, TD_RIGHT);
        else
        {
            (close(pfds[0]), close(pfds[1]), waitpid(pidl, &status, 0), waitpid(pidr, &status, 0));
            g_minishell.sigint_child = false;
            return (ft_get_exit_status(status));
        }
    }
    return ENO_GENERAL;
}