#include "minishell.h"

/*
    Advance past the $ and mark the start of the variable name.
    If the very next character is ?, write the shell’s last exit status (g_minishell.exit_s) to fd and return 2 (we consumed $?).
    Otherwise, scan forward until you hit a space, another $, or end‐of‐string.
    If there was at least one character in that range, extract it (ft_substr), look up its value in the shell’s environment (ft_get_envlst_val), and write that value to fd.
    Return the total number of characters consumed (so the caller can skip ahead past the $VAR).
*/
static int ft_heredoc_expand_writer(char *str, size_t i, int fd)
{
    size_t start = ++i;
    char *temp;
    if (str[i] == '?')
        return (ft_putnbr_fd(g_minishell.exit_s, fd), 2);
    while (str[i] && str[i] != '$' && str[i] != ' ')
        i++;
    if (i != start)
    {
        temp = ft_garbage_collector(ft_substr(str, start, i), false);
        temp = ft_get_envlst_val(temp);
        if (temp)
            ft_putstr_fd(temp, fd);
    }
    return i;
}

/*
    walks through the string char by char
    expand the variable if $ is found and advance i by the number of characters written
    o/w copy literal chars one by one to the fd
    finally, write a newline to the fd to terminate the heredoc input
*/
void ft_heredoc_expander(char *str, int fd)
{
    size_t i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            i += ft_heredoc_expand_writer(str, i, fd);
        else
            i += (ft_putchar_fd(str[i], fd), 1);
    }
    ft_putchar_fd('\n', fd);
}