#include "minishell.h"

// checks if a string contains an asterisk
bool ft_contains_asterisk(char *str)
{
    size_t i = 0;
    ;
    while (str[i])
    {
        if (str[i] == '*')
            return true;
        i++;
    }
    return false;
}

// returns the length of NULL terminated array of strings
size_t ft_str_arr_len(char **str_arr)
{
    size_t i = 0;
    while (str_arr[i])
        i++;
    return i;
}

// counts how many files/directories in curr dir match the pattern
size_t ft_match_count(char *pattern)
{
    DIR *dir;
    size_t match_count = 0;
    struct dirent *entry;
    dir = opendir(".");
    entry = readdir(dir);
    while (entry)
    {
        if (ft_match_star(pattern, entry->d_name))
            match_count++;
        entry = readdir(dir);
    }
    closedir(dir);
    return match_count;
}

// counts the total number of strings across 2D array of strings
static size_t ft_multi_arr_strs_count(char ***str_arrs)
{
    size_t i = 0, j, strs_count = 0;
    while (str_arrs[i])
    {
        j = 0;
        while (str_arrs[i][j])
            j++;
        strs_count += j;
        i++;
    }
    return strs_count;
}

// flattens the 2D array of strings into a single array of strings
char **ft_join_str_arrs(char ***str_arrs)
{
    size_t i, j, strs_count = ft_multi_arr_strs_count(str_arrs);
    char **joined = (char **)ft_calloc(strs_count + 1, sizeof(char *));
    i = 0;
    strs_count = 0;
    while (str_arrs[i])
    {
        j = 0;
        while (str_arrs[i][j])
        {
            joined[strs_count + j] = ft_strdup(str_arrs[i][j]);
            j++;
        }
        strs_count += j;
        i++;
    }
    return (ft_free_char3(str_arrs), joined);
}