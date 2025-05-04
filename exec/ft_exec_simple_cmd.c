#include "minishell.h"

// iterates through all the redirections of the command
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

// restore the standard input and output
void ft_reset_stds(bool piped)
{
    if (piped)
        return;
    dup2(g_minishell.stdin, 0);
    dup2(g_minishell.stdout, 1);
}

// forks a child for the external command execution
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

// executes a simple command
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