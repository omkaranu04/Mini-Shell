#include "minishell.h"

/*
    this function enforces that dotfiles only match patterns that also begin with a dot
    and the non dotfiles only match with the non dotfile patterns
    returns true if both the pattern and filename share same hidden status
*/
static bool ft_matches_visibility(char *pattern, char *str)
{
    if ((pattern[0] == '.' && str[0] == '.') || (pattern[0] != '.' && str[0] != '.'))
        return true;
    return false;
}

/*
    a wraparound on the readdir function
    it reads the next directory entry from the open DIR*
    ans stores in the provided pointer
*/
static bool ft_set_direntry(struct dirent **entry, DIR *dir)
{
    *entry = readdir(dir);
    return true;
}

/*
    counts how many filenames match its pattern using ft_match_count
    if the word has no * or no matches are found, it returns a two element array containing the original word and NULL
    else it opens the current directory
        uses the ft_match_star to test the filename against the pattern
        uses the ft_matches_visibility to skip dotfiles when pattern not start with .
        duplicates each matching filename in the result array
*/
static char **ft_globber_helper(char *str)
{
    char **returned;
    DIR *dir;
    struct dirent *entry;
    size_t match_count = ft_match_count(str);
    if (!ft_contains_asterisk(str) || !match_count)
    {
        returned = (char **)ft_calloc(2, sizeof(char *));
        returned[0] = ft_strdup(str);
        return returned;
    }
    else
    {
        dir = opendir(".");
        returned = (char **)ft_calloc(match_count + 1, sizeof(char *));
        match_count = 0;
        while (ft_set_direntry(&entry, dir) && entry)
        {
            if (ft_match_star(str, entry->d_name) && ft_matches_visibility(str, entry->d_name))
                returned[match_count++] = ft_strdup(entry->d_name);
        }
        closedir(dir);
    }
    return returned;
}

/*
    applies globbing across an array of expanded words
    ft_globber_helper is used to fill the 3D array to hold each word's match list
    falttens and concatenaates all per-word match listst into single NULL terminates array
    returns the final list of filenames
*/
char **ft_globber(char **expanded)
{
    size_t i = 0, expanded_len = ft_str_arr_len(expanded);
    char ***globbed;
    globbed = (char ***)ft_calloc(expanded_len + 1, sizeof(char **));
    while (expanded[i])
    {
        globbed[i] = ft_globber_helper(expanded[i]);
        i++;
    }
    return (ft_free_char2(expanded), ft_join_str_arrs(globbed));
}