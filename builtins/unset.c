#include "minishell.h"

/*
    the function removes a specific env var from the shell's
    env list given the key
*/
static void ft_unset_helper(char *key)
{
    t_env *curr, *prev;
    prev = NULL;
    curr = g_minishell.envlst;
    while (curr)
    {
        if (!ft_strcmp(key, curr->key))
        {
            if (prev)
                prev->next = curr->next;
            else
                g_minishell.envlst = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

/*
    the function implements the main unset command logic
    the function validates the key name using the ft_check_key
    and if the key is found and then helper function is called
    to remove the variable from the env list
*/
int ft_unset(char **args)
{
    int i = 1;
    bool err;
    if (!args[1])
        return 0;
    err = false;
    while (args[i])
    {
        if (!ft_check_key(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            err = true;
        }
        else
            ft_unset_helper(ft_garbage_collector(ft_extract_key(args[i]), false));
        i++;
    }
    return err;
}