#include "minishell.h"

// funcntion to check if the string has '-n' option which in bash
// supresses the newline
static int ft_check_option(char *s)
{
    int i = 0;
    if (s[0] != '-')
        return 0;
    i++;
    while (s[i])
    {
        if (s[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

// implements the echo command, handling options and argument printing
int ft_echo(char **args)
{
    int i = 1, opt = 0;
    while (args[i] != NULL && ft_check_option(args[i]) == 1)
    {
        opt = 1;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (opt == 0)
        ft_putstr_fd("\n", 1);
    return 0;
}