#include "minishell.h"

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