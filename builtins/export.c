#include "minishell.h"

// print the error message for invalid variable name
static int ft_export_err_msg(char *identifier)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(identifier, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
    return 1;
}

// prints all exported env var in the format in the printf line, escaping the $ and " just like bash does
static void ft_export_list(void)
{
    t_env *list;
    size_t i;
    list = g_minishell.envlst;
    while (list)
    {
        if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
        {
            printf("declare -x %s=\"", list->key);
            i = 0;
            while ((list->value)[i])
            {
                if ((list->value)[i] == '$' || (list->value)[i] == '"')
                    printf("\\%c", (list->value)[i++]);
                else
                    printf("%c", (list->value)[i++]);
            }
            printf("\"\n");
        }
        else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
            printf("declare -x %s\n", list->key);
        list = list->next;
    }
}

// checks if a string is a valid env var name according to the shell rules
int ft_check_key(char *str)
{
    int i = 1;
    if (!ft_isalpha(*str) && *str != '_')
        return 0;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

// implements the export builtin command
int ft_export(char **argv)
{
    int i = 1, exit_s = 0;
    char *key;
    if (!argv[1])
        return (ft_export_list(), 0);
    while (argv[i])
    {
        if (ft_check_key(argv[i]) == 0)
            exit_s = ft_export_err_msg(argv[i]);
        else
        {
            key = ft_extract_key(argv[i]);
            if (ft_env_entry_exists(key))
                ft_update_envlst(key, ft_extract_value(argv[i]), false);
            else
                ft_update_envlst(key, ft_extract_value(argv[i]), true);
        }
        i++;
    }
    return exit_s;
}