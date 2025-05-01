#include "minishell.h"

// checks if the env var with the given key exists in the env list
bool ft_env_entry_exists(char *key)
{
    t_env *envlist;
    envlist = g_minishell.envlst;
    while (envlist)
    {
        if (!ft_strcmp(key, envlist->key))
            return true;
        envlist = envlist->next;
    }
    return false;
}

// creates a new env var node with the given key and value
static t_env *ft_envlst_new(char *key, char *value)
{
    t_env *new_;
    new_ = (t_env *)ft_calloc(1, sizeof(t_env));
    if (!new_)
        return NULL;
    new_->key = ft_garbage_collector(ft_strdup(key), false);
    if (value)
        new_->value = ft_garbage_collector(ft_strdup(value), false);
    new_->next = NULL;
    return new_;
}

// retrieves the value of the env var with the given key
char *ft_get_envlst_val(char *key)
{
    t_env *envlist;
    envlist = g_minishell.envlst;
    while (envlist)
    {
        if (!ft_strcmp(key, envlist->key))
            return envlist->value;
        envlist = envlist->next;
    }
    return NULL;
}

// appends a new env var node to the end of the env list
void ft_envlst_back(t_env *new_)
{
    t_env *curr;
    if (!g_minishell.envlst)
    {
        g_minishell.envlst = new_;
        return;
    }
    curr = g_minishell.envlst;
    while (curr && curr->next)
        curr = curr->next;
    curr->next = new_;
}

// updates the value of an env var if it exists, or creates it if not and 'create' is true
void ft_update_envlst(char *key, char *value, bool create)
{
    t_env *envlist;
    envlist = g_minishell.envlst;
    while (envlist)
    {
        if (!ft_strcmp(key, envlist->key))
        {
            if (value)
                envlist->value = ft_garbage_collector(ft_strdup(value), false);
            return;
        }
        envlist = envlist->next;
    }
    if (create)
        ft_envlst_back(ft_envlst_new(key, value));
}