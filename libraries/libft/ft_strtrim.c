#include "libft.h"

// c -> char to be checked, set -> a string of chaars to match against
// if match then return 1, else return 0
static int ft_matchset(char c, char const *set)
{
    size_t i = 0;
    while (set[i])
    {
        if (set[i] == c)
            return 1;
        i++;
    }
    return 0;
}

// s1 -> the inpput string to trim, set -> the set of chars to trim
// returns the trimmed string
static char *ft_trimmer(char const *s1, char const *set)
{
    size_t i = 0, j = 0;
    char *trimmed;
    while (s1[i] && ft_matchset(s1[i], set))
        i++;
    while (s1[i + j])
        j++;
    while (j && ft_matchset(s1[i + j - 1], set))
        j--;
    trimmed = ft_calloc(j + 1, sizeof(char));
    if (!trimmed)
        return NULL;
    while (j && j--)
        trimmed[j] = s1[i + j];
    return trimmed;
}

// main entry point for the fuction calls
// s1 -> the input string to trim, set -> the set of chars to trim
char *ft_strtrim(char const *s1, char const *set)
{
    if (!s1 || !set)
        return NULL;
    return ft_trimmer(s1, set);
}