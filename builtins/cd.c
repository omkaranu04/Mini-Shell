#include "minishell.h"

/*
    function updates the PWD environment variable to reflect
    the current working directory
    helper function ft_update_envlst is used to update the 
    value of the PWD variable in the environment list
    returns 0 on success, 1 on failure
*/
static int ft_change_pwd(void)
{
    char *cwd; 
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return 1;
    return (ft_update_envlst("PWD", cwd, false), 0);
}

/*
    function handles cd command without any arguments, which means cd to home directory
    first, it updates the OLDPWD to the cirrent working directory saved in PWD
    gets the value of the HOME environment variable, changes the directory to it using chdir
    upadtes the PWD to the home (new) directory
    returns 0 on success, 1 on failure
*/
static int ft_cd_home(void)
{
    char *home;
    ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
    home = ft_get_envlst_val("HOME");
    if (!home)
        return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
    if (chdir(home) == ENO_SUCCESS)
        return (ft_update_envlst("PWD", home, false), 0);
    return 1;
}

/*
    function formats and prints an error message when directory cannot be found
*/
static int fd_cd_err_msg(char *err_msg)
{
    ft_putstr_fd("minishell: cd: `", 2);
    ft_putstr_fd(err_msg, 2);
    ft_putstr_fd("': No such file or directory\n", 2);
    return 1;
}

/*
    function to handle the cd command
    if no path is given calls ft_cd_home
    else change the directory to the given path using chdir
*/
int ft_cd(char *path)
{
    if (!path)
        return ft_cd_home();
    if (chdir(path) != ENO_SUCCESS)
        return fd_cd_err_msg(path);
    ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
    return ft_change_pwd();
}