#include "minishell.h"

// ensurees that the hidden files are included only if the pattern explicitly includes so
static bool ft_matches_visibility(char *pattern, char *str)
{
    if ((pattern[0] == '.' && str[0] == '.') || (pattern[0] != '.' && str[0] != '.'))
        return true;
    return false;
}

// reads the next directory entry from the stream
static bool ft_set_direntry(struct dirent **entry, DIR *dir)
{
    *entry = readdir(dir);
    return true;
}

// outputs an array of matching filenames, or original string if no matches
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

// main function to handle globbing
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