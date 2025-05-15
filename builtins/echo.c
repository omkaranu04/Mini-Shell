#include "minishell.h"

/*
    function cheks if the string is a valid '-n'
    option for the echo command
*/
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

/*
    "the -n option in echo suppresses the trailing newline"
    starts by checking for options in the commmand, sets oopt to 1 if -n is present
    then it prints remaining args to stdout, adds space between args except for the last one
    if no -n option is present, it adds a newline at the end
    returns 0 on success
*/
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