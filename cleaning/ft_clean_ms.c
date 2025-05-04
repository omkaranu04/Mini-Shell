#include "minishell.h"

// frees all the nodes in the shell's env var linked list
static void ft_clear_envlist(void)
{
    t_env *envlst, *envlst_tofree;
    envlst = g_minishell.envlst;
    while (envlst)
    {
        envlst_tofree = envlst;
        envlst = envlst->next;
        free(envlst_tofree);
    }
    g_minishell.envlst = NULL;
}

// performs all the cleaning operations for the shell
void ft_clean_ms(void)
{
    ft_garbage_collector(NULL, true);
    ft_clear_ast(&g_minishell.ast);
    ft_clear_envlist();
    rl_clear_history();
    tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
}