#include "minishell.h"

/*
    handles the output redirection
    first check if the expanded filename is valid
    if valid then open the file in specified mode (O_TRUNC here erases existing content and rewrites the file)
    and then redirect the output to the desired fd using the dup2 command
*/
int ft_out(t_io_node *io_list, int *status)
{
    int fd;
    if (!io_list->expanded_value || io_list->expanded_value[1])
    {
        *status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
        return (*status);
    }
    fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        *status = ft_err_msg(ft_check_write(io_list->expanded_value[0]));
        return (*status);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    *status = 0;
    return (*status);
}

/*
    handles the input redirection
    first check if the expanded filename is valid
    if valid then open the file in specified mode
    and then redirect the input to the desired fd using the dup2 command
*/
int ft_in(t_io_node *io_list, int *status)
{
    int fd;
    if (!io_list->expanded_value || io_list->expanded_value[1])
    {
        *status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
        return (*status);
    }
    fd = open(io_list->expanded_value[0], O_RDONLY);
    if (fd == -1)
    {
        *status = ft_err_msg(ft_check_read(io_list->expanded_value[0]));
        return (*status);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    *status = 0;
    return (*status);
}

/*
    handles the append redirection
    first check if the expanded filename is valid
    if valid then open the file in specified mode (O_APPEND here is necessary)
    and then redirect the output to the desired fd using the dup2 command
*/
int ft_append(t_io_node *io_list, int *status)
{
    int fd;
    if (!io_list->expanded_value || io_list->expanded_value[1])
    {
        *status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
        return (*status);
    }
    fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
    {
        *status = ft_err_msg(ft_check_write(io_list->expanded_value[0]));
        return (*status);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    *status = 0;
    return 0;
}