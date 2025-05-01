#include "minishell.h"
/*
    - Change to aa specified directory
    - Change to HOME if no argument is given
    - Error handling for missing directories or unset HOME
    - Updating the PWD and OLDPWD environment variables
*/

// updates the pwd env var to curr working directory after cd
static int ft_change_pwd(void)
{
    char *cwd; // get current working directory
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return 1;
    return (ft_update_envlist("PWD", cwd, false), 0);
}

// user runs cd with no args
static int ft_cd_home(void)
{
    char *home;
    ft_update_envlist("OLDPWD", ft_get_envlist_val("PWD"), false);
    home = ft_get_envlist_val("HOME");
    if (!home)
        return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
    if (chdir(home) == ENO_SUCCESS)
        return (ft_update_envlist("PWD", home, false), 0);
    return 1;
}

// user runs cd with a path that doesn't exist
// prints error message
static int fd_cd_err_msg(char *err_msg)
{
    ft_putstr_fd("minishell: cd: `", 2);
    ft_putstr_fd(err_msg, 2);
    ft_putstr_fd("': No such file or directory\n", 2);
    return 1;
}

// main function for the cd command
int ft_cd(char *path)
{
    if (!path)
        return ft_cd_home();
    if (chdir(path) != ENO_SUCCESS)
        return ft_cd_err_msg(path);
    ft_update_envlist("OLDPWD", ft_get_envlist_val("PWD"), false);
    return ft_change_pwd();
}