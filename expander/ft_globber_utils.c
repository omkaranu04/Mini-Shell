#include "minishell.h"

// checks if a given string contains the * character
bool ft_contains_asterisk(char *str)
{
    size_t i = 0;
    while (str[i])
    {
        if (str[i] == '*')
            return true;
        i++;
    }
    return false;
}

// counts the number of entries in a NULL terminated array of strings
size_t ft_str_arr_len(char **str_arr)
{
    size_t i = 0;
    while (str_arr[i])
        i++;
    return i;
}

/*
    opens the current directory, iterates all filenames ans uses the ft_match_star to test
    each name against the pattern, returns how many filenames matched
*/
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

// returns the count of strings in each of the string arrays within the str_arrs
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

// flattens and concatenates a 3D array of strings into a single NULL terminated array
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