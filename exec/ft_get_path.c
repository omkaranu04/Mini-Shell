#include "minishell.h"

/*
    the function searches for a command in the directories specified in the PATH env var
    the funtion iterates thorugh each directory in the path, constructs the potential command by joining the directory path
    with the command name using '/'
    if an executable is found it returns the t_path with error code and path to the executable
    else returns with the command not found error
*/
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

/*
    the main function to resolve the command paths
    if the command conatins '/' it indicates a relative/absolute path rather than bare commaand name
    in such a case it directly checks if the given path is executable
    else it calls the ft_get_env_path after retrieving the PATH var using the ft_get_envlst_val
*/
t_path ft_get_path(char *cmd)
{
    char *value;
    if (*cmd == '\0')
        return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
    if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
        return ((t_path){ft_check_exec(cmd, false), cmd});
    value = ft_get_envlst_val("PATH");
    if (value)
        return ft_get_env_path(value, cmd);
    return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, cmd}, NULL});
}