#include "minishell.h"

/*
    the function extracts the key portion of the
    env var string
    if no equal sign is found it returns a duplicate of the entire string
*/
char *ft_extract_key(char *str)
{
    size_t i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return ft_garbage_collector(ft_substr(str, 0, i), false);
        i++;
    }
    return ft_strdup(str);
}

/*
    the funtion extracts the value portion of the
    env var string
    if no equal sign is found it returns NULL
*/
char *ft_extract_value(char *str)
{
    size_t i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            i++;
            return ft_garbage_collector(ft_substr(str, i, ft_strlen(str) - i), false);
        }
        i++;
    }
    return NULL;
}

/*
    "used to populate the internal env from the system's env"
    the function initializes the shell's env var linked list
    it iterates through the environ array, for each of the string it extracts
    it adds the key-value pair after extracting
*/
void ft_init_envlst(void)
{
    int i;
    char **environ, *key, *value;
    environ = g_minishell.environ;
    if (!environ)
        return;
    i = 0;
    while (environ[i])
    {
        key = ft_extract_key(environ[i]);
        value = ft_extract_value(environ[i]);
        ft_update_envlst(key, value, true);
        i++;
    }
}

/*
    the function prints the env vars to stdout
*/
int ft_env(void)
{
    t_env *list;
    list = g_minishell.envlst;
    while (list)
    {
        if (list->value != NULL)
            printf("%s=%s\n", list->key, list->value);
        list = list->next;
    }
    return ENO_SUCCESS;
}