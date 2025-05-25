#include "minishell.h"

/*
    the function processes all IO redirections for a command
    it iterates through the linked list of the IO nodes in the command node
    for each of the IO node checks and:
        - I_OUT: calls ft_out function
        - IO_IN: calls ft_in function
        - IO_APPEND: calls ft_append function
        - IO_HEREDOC: redirects the stdin from the heredoc file descriptor and closes it
    if any of the redirection fails then it returns the error status
    if all redirections are successful then it returns ENO_SUCCESS
*/
int ft_check_redirection(t_node *node)
{
    t_io_node *tmp_io;
    int tmp_status;
    tmp_io = node->io_list;
    while (tmp_io)
    {
        if (tmp_io->type == IO_OUT && ft_out(tmp_io, &tmp_status) != ENO_SUCCESS)
            return tmp_status;
        else if (tmp_io->type == IO_IN && ft_in(tmp_io, &tmp_status) != ENO_SUCCESS)
            return tmp_status;
        else if (tmp_io->type == IO_APPEND && ft_append(tmp_io, &tmp_status) != ENO_SUCCESS)
            return tmp_status;
        else if (tmp_io->type == IO_HEREDOC)
            (dup2(tmp_io->here_doc, 0), close(tmp_io->here_doc));
        tmp_io = tmp_io->next;
    }
    return ENO_SUCCESS;
}

/*
    the function is used to reset the stdin and stdout fds
    to their default values
*/
void ft_reset_stds(bool piped)
{
    if (piped)
        return;
    dup2(g_minishell.stdin, 0);
    dup2(g_minishell.stdout, 1);
}

/*
    the function executes an external command in a child process
    sets a flag to indicate a child process is running
    forks a child process
    in child process:
        - applies all redirections using the ft_check_redirection
        - resolves the cmd path using the ft_get_path
        - attempts to execute the command using execve
    in parent process:
        - waits for the child process to finish
        - resets the child process flag
*/
static int ft_exec_child(t_node *node)
{
    t_path path_status;
    int tmp_status, fork_pid;
    g_minishell.sigint_child = true;
    fork_pid = fork();
    if (!fork_pid)
    {
        tmp_status = ft_check_redirection(node);
        if (tmp_status != ENO_SUCCESS)
            (ft_clean_ms(), exit(ENO_GENERAL));
        path_status = ft_get_path((node->expanded_args)[0]);
        if (path_status.err.no != ENO_SUCCESS)
        {
            tmp_status = ft_err_msg(path_status.err);
            (ft_clean_ms(), exit(tmp_status));
        }
        if (execve(path_status.path, node->expanded_args, g_minishell.environ) == -1)
            (ft_clean_ms(), exit(1));
    }
    waitpid(fork_pid, &tmp_status, 0);
    g_minishell.sigint_child = false;
    return (ft_get_exit_status(tmp_status));
}

/*
    the main function to execute simple command node
    if there are no args
        - applies any redirections
        - resets the stdin and stdout fds
        - returns ENO_GENERAL
    if the command is a builtin
        - applies redirections
        - executes the builtin command
        - resets the stdin and stdout fds
    for any other command
        - calls the ft_exec_child to fork and execute command
*/
int ft_exec_simple_cmd(t_node *node, bool piped)
{
    int tmp_status;
    if (!node->expanded_args)
    {
        tmp_status = ft_check_redirection(node);
        return (ft_reset_stds(piped), (tmp_status && ENO_GENERAL));
    }
    else if (ft_is_builtin((node->expanded_args)[0]))
    {
        tmp_status = ft_check_redirection(node);
        if (tmp_status != ENO_SUCCESS)
            return (ft_reset_stds(piped), ENO_GENERAL);
        tmp_status = ft_exec_builtin(node->expanded_args);
        return (ft_reset_stds(piped), tmp_status);
    }
    else
        return (ft_exec_child(node));
}