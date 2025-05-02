#include "minishell.h"

// tracks whether the pattern is currently inside single or double quotes
static void ft_handle_pattern_quotes(char **pattern, char *quotes)
{
    if (**pattern == '"' || **pattern == '\'')
    {
        if (!*quotes)
            *quotes = *(*pattern)++;
        else
        {
            if (*quotes == **pattern)
            {
                *quotes = 0;
                (*pattern)++;
            }
        }
    }
}

// skips over any leading '*' characters in the pattern
static bool ft_handle_stars(char **pattern, char **last_wildcard, char **last_match, char *str)
{
    while (**pattern == '*')
        (*pattern)++;
    if (!**pattern)
        return true;
    *last_wildcard = *pattern;
    *last_match = str;
    return false;
}

// if the current pattern and string match, move to the next character in both
static bool ft_pattern_match_exists(char **pattern, char **last_wildcard, char **last_match, char **str)
{
    if (**pattern == **str)
    {
        (*pattern)++;
        (*str)++;
        return true;
    }
    else if (*last_wildcard)
    {
        *str = ++(*last_match);
        *pattern = *last_wildcard;
        return true;
    }
    else
        return false;
}

// initializes pointers for tracking the last wildcard and last match
bool ft_match_star(char *pattern, char *str)
{
    char *last_wildcard, *last_match, quotes;
    quotes = 0;
    last_wildcard = NULL;
    last_match = NULL;
    while (*str)
    {
        ft_handle_pattern_quotes(&pattern, &quotes);
        if (*pattern == '*' && !quotes && ft_handle_stars(&pattern, &last_wildcard, &last_match, str))
            return true;
        else if (!ft_pattern_match_exists(&pattern, &last_wildcard, &last_match, &str))
            return false;
    }
    if (*pattern == '*')
        while (*pattern == '*')
            pattern++;
    return (!*pattern);
}