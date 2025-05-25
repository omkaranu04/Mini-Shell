#include "minishell.h"

/*
    makes the function calls for the builtin commands as specified
    in th builtins directory
    the function returns the exit status of the builtin command
*/
int ft_exec_builtin(char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return ft_echo(args);
    if (ft_strcmp(args[0], "cd") == 0)
        return ft_cd(args[1]);
    if (ft_strcmp(args[0], "env") == 0)
        return ft_env();
    if (ft_strcmp(args[0], "pwd") == 0)
        return ft_pwd();
    if (ft_strcmp(args[0], "export") == 0)
        return ft_export(args);
    if (ft_strcmp(args[0], "unset") == 0)
        return ft_unset(args);
    ft_exit(args);
    return ENO_GENERAL;
}

/*
    checks if the user typed cmd is any of the biltin command
*/
bool ft_is_builtin(char *arg)
{
    if (!arg)
        return false;
    if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd") || !ft_strcmp(arg, "env") ||
        !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset") ||
        !ft_strcmp(arg, "exit"))
        return true;
    return false;
}