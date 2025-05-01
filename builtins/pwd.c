#include "minishell.h"

// implements the pwd command
// prints the current working directory
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