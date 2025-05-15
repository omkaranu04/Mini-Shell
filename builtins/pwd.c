#include "minishell.h"

/*
    extracts the current working directory
    ans then outputs it to stdout
*/
int ft_pwd(void)
{
    char *cwd;
    cwd = NULL;
    cwd = getcwd(cwd, 0);
    if (!cwd)
        return 1;
    ft_putstr_fd(cwd, 1);
    ft_putstr_fd("\n", 1);
    return 0;
}