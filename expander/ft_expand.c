#include "minishell.h"

/*
    it parses and expands a $ expression at str[*i] and returns the expansion
    it advances past the $ symbol
    if the next char is a digit or '@', returns emoty string, since the forms are not supported
    if the next char is '?', returns shells last exit code as string
    if the next char is not a valid variable name character, returns "$" literally
    else it reads the var name, searches for it in env list and then returns its value
*/
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

/*
    scans an input string character by character, building a new string ret in which
    Single-quoted segments ('…') are copied verbatim by calling ft_handle_squotes.
    Double-quoted segments ("…" ) call ft_handle_dquotes, which in turn handles any $ inside them.
    Dollar signs outside of single quotes invoke ft_handle_dollar.
    Plain text (no $ or quotes) is gathered by ft_handle_normal_str.
*/
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

/*
    Top‐level expansion for one word:
    Pre-expansion: Calls ft_cmd_pre_expander to resolve $ and preserve quoted regions.
    Clean empty quotes: Removes any '' or "" pairs that became empty after expansion (ft_clean_empty_strs).
    Splitting: Breaks the single string into an array of words using shell word-splitting rules (ft_expander_split).
    Globbing: For each word containing *, matches it against filenames in the current directory (ft_globber), replacing it with matching names.
    Strip quotes: Removes all remaining quote characters from each final word (ft_strip_quotes).
    The result is a NULL-terminated array of fully expanded, split, globbed, and unquoted strings ready to be passed as argv to a command.
*/
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