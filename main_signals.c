#include "minishell.h"

/*
    SIGINT signal handler
    if the sigint_child flag is set that means the minishell is in child or heredoc reader:
        - print a newline to cleanly end the current input
        - clear the sigint_child flag
        - mark that heredoc was aborted by SIGINT
    else:
        - print a newline to cleanly end the current input
        - clear the current line in readline
        - move to a new line and redisplay the prompt
*/
static void ft_sigint_handler(int num)
{
    (void)num;
    if (g_minishell.sigint_child)
    {
        ft_putstr_fd("\n", 1);
        g_minishell.sigint_child = false;
        g_minishell.heredoc_sigint = true;
    }
    else
    {
        ft_putstr_fd("\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

/*
    SIGQUIT signal handler
    prints "Quit: 3" to standard output
*/
void ft_sigquit_handler(int num)
{
    (void)num;
    ft_putstr_fd("Quit: 3\n", 1);
}

/*
    take the shell's original terminal settings,
    disable the ECHOCTL flag to prevent control characters from being echoed
    set the SIGINT handler to ft_sigint_handler
    set the SIGQUIT handler to SIG_IGN (ignore)
    initialize the heredoc_sigint and sigint_child flags to false
*/
void ft_init_signals(void)
{
    struct termios term;
    term = g_minishell.original_term;
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    g_minishell.heredoc_sigint = false;
    g_minishell.sigint_child = false;
    signal(SIGINT, ft_sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}