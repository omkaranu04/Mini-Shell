#include "minishell.h"

/*
    the function is used to clear the env var linked list
    and sets the list pointer to NULL
*/
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

/*
    the function is the main cleanup for the entire minishell
    called at the end of the program
*/
void ft_clean_ms(void)
{
    ft_garbage_collector(NULL, true);
    ft_clear_ast(&g_minishell.ast);
    ft_clear_envlist();
    rl_clear_history();
    tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
}