#include "minishell.h"

// expands the shell variables within a string
char *ft_handle_dollar(char *str, size_t *i)
{
    size_t start;
    char *var, *env_val;
    (*i)++;
    if (ft_isdigit(str[*i]) || str[*i] == '@')
    {
        (*i)++;
        return ft_strdup("");
    }
    else if (str[*i] == '?')
    {
        (*i)++;
        return ft_itoa(g_minishell.exit_s);
    }
    else if (!ft_is_valid_var_char(str[*i]))
        return ft_strdup("$");
    start = *i;
    while (ft_is_valid_var_char(str[*i]))
        (*i)++;
    var = ft_substr(str, start, *i - start);
    env_val = ft_get_envlst_val(var);
    if (!env_val)
        return (free(var), ft_strdup(""));
    return (free(var), ft_strdup(env_val));
}

// parses a command string, handling the single and double quotes, vars and unquoted texts
static char *ft_cmd_pre_expander(char *str)
{
    char *ret = ft_strdup("");
    size_t i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            ret = ft_strjoin_f(ret, ft_handle_squotes(str, &i));
        else if (str[i] == '"')
            ret = ft_strjoin_f(ret, ft_handle_dquotes(str, &i));
        else if (str[i] == '$')
            ret = ft_strjoin_f(ret, ft_handle_dollar(str, &i));
        else
            ret = ft_strjoin_f(ret, ft_handle_normal_str(str, &i));
    }
    return ret;
}

// handles the whole expansion of a command process
char **ft_expand(char *str)
{
    char **expanded, **globbed;
    size_t i;
    str = ft_cmd_pre_expander(str);
    if (!str)
        return NULL;
    str = ft_clean_empty_strs(str);
    if (!str)
        return NULL;
    expanded = ft_expander_split(str);
    free(str);
    if (!expanded)
        return NULL;
    globbed = ft_globber(expanded);
    if (!globbed)
        return NULL;
    i = 0;
    while (globbed[i])
    {
        globbed[i] = ft_strip_quotes(globbed[i]);
        i++;
    }
    return globbed;
}