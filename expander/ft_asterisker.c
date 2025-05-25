#include "minishell.h"

/*
    tracks the quoted segments in the pattern so that wildcards in the quotes get
    treated literally instead of as special characters.
*/
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

/*
    handles one or more consecutive '*' characters in the pattern.
    consumes all the leading *s
    if the pattern ends right after ths *s, returns true
    o/w, records the position of the last wildcard and the last match
*/
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

/*
    attempts to match s single pattern character against the cirrent string character
    if it does match then return true
    if not, but if there is a last wildcaard it backtracks
    moves the pointer 1 past the last match point, resets the pattern pointer to last wildcard
    and returns true to continue matching
*/
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

/*
    matches a pattern against a string, handling wildcards and quoted segments.
    The pattern can contain '*' characters that match any sequence of characters,
    and quoted segments that treat wildcards literally.
    Returns true if the pattern matches the string, false otherwise.
*/
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