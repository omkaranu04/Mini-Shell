#include "minishell.h"

/*
    checks if the string consists of onlyy digits
    used ot validate that exit arguments are numericH
*/
static bool ft_isnumber(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return false;
        i++;
    }
    return true;
}

/*
    handles the whitespaces and sign characters at the beginning of the string
    increments the index and updates the sign variable
*/
static void ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
    while (s[*i] && s[*i] == ' ')
        (*i)++;
    if (s[*i] == '+' || s[*i] == '-')
    {
        if (s[*i] == '-')
            *sign *= -1;
        (*i)++;
    }
}

/*
    funnction converts a string to an integer for the exit status
*/
static int ft_exittoi(char *s)
{
    int i = 0, sign = 1, exit_s;
    unsigned long long result;
    ft_skip_spaces_and_get_sign(s, &i, &sign);
    if (!ft_isnumber(s + i))
    {
        exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
        (ft_clean_ms(), exit(exit_s));
    }
    result = 0;
    while (s[i])
    {
        result = (result * 10) + (s[i] - '0');
        if (result > LONG_MAX)
        {
            exit_s = ft_err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
            (ft_clean_ms(), exit(exit_s));
        }
        i++;
    }
    return ((result * sign) % 256);
}

/*
    implements the exit builtin command
    it initialises the exit_s with the current exit status from the global state
    if valid arg proceed, o/w print error message
    finally cleans up the shell resources and exits wuth the determined status
*/
void ft_exit(char **args)
{
    int exit_s = g_minishell.exit_s;
    if (args[1])
    {
        if (args[2] && ft_isnumber(args[1]))
        {
            exit_s = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
            (ft_clean_ms(), exit(exit_s));
        }
        else
            exit_s = ft_exittoi(args[1]);
    }
    (ft_clean_ms(), exit(exit_s));
}