#include "minishell.h"

/*
    function handles the execution of the child process in a pipeline
    the direction indicates -> left (writing) or right (reading) side of the pipe
    for the left side of the pipe
        - closes the read end of the pipe
        - redirects the stdout to the write end of the pipe
        - closes the write end of the pipe
    for the right side of the pipe
        - closes the write end of the pipe
        - redirects the stdin to the read end of the pipe
        - closes the read end of the pipe
    recursivly executes the node with ft_exec_node, marking it as part of pipe
*/
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

/*
    the function is used to interpret the status value returned
    by the waitpid function
*/
int ft_get_exit_status(int status)
{
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (WEXITSTATUS(status));
}

/*
    the function executes a pipeline node (cmds connected by |)
    it sets a flag to indicate that the child process is running. and creates a pipe
    forks a child for the left side of the pipe and calls the ft_exec_pipe_child 
    the parent forks another child for the right side of the pipe and calls the ft_exec_pipe_child

    in the parent process
        - closes both ends of the pipe
        - waits for both child processes to finish
        - resets the child process flag
        - returns the exit status of the last child process
*/
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

/*
    the main recursive function for executnig an AST node
    handles different node types:
        - N_PIPE: calls the ft_exec_pipeline function
        - N_AND: execs left side and then right only if left succeeds
        - N_OR: execs left side and then right only if left fails
        - N_CMD: calls the ft_exec_simple_cmd function
*/
int ft_exec_node(t_node *tree, bool piped)
{
    int status;
    if (!tree)
        return 1;
    if (tree->type == N_PIPE)
        return ft_exec_pipeline(tree);
    else if (tree->type == N_AND)
    {
        status = ft_exec_node(tree->left, false);
        if (status == ENO_SUCCESS)
            return ft_exec_node(tree->right, false);
        return status;
    }
    else if (tree->type == N_OR)
    {
        status = ft_exec_node(tree->left, false);
        if (status == ENO_SUCCESS)
            return status;
        return ft_exec_node(tree->right, false);
    }
    else
        return ft_exec_simple_cmd(tree, piped);
    return ENO_GENERAL;
}