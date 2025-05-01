#include "minishell.h"

static t_path ft_get_env_path(char *path, char *cmd)
{
    size_t i = 0;
    t_err err;
    char *cmd_path, **split_path;
    split_path = ft_split(path, ':');
    while (split_path[i])
    {
        cmd_path = ft_garbage_collector(ft_strjoin_with_f(ft_strdup(split_path[i]), ft_strdup(cmd), '/'), false);
        err = ft_check_exec(cmd_path, true);
        if (err.no == ENO_SUCCESS)
            return ((t_path){(t_err){ENO_SUCCESS, 42, cmd_path}, cmd_path});
        i++;
    }
    ft_free_char2(split_path);
    return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
}