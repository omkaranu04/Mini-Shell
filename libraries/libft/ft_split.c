#include "libft.h"

// returns the count of substrings will be created
// given the string s and the delimiter c
static size_t ft_count(char const *s, char c)
{
    size_t count = 0, i = 0;
    while (s[i])
    {
        if (s[i] != c && ++count)
            while (s[i] && s[i] != c)
                i++;
        while (s[i] && s[i] == c)
            i++;
    }
    return count;
}

// for each substring taht we have found using the same logic as in the ft_count above
// we will allocate the memory using the size of the substring using ft_calloc
static char **ft_allocator(char const *s, char c, char **strs)
{
    size_t cnt, i = 0, j = 0;
    while (s[i])
    {
        cnt = 0;
        if (s[i] != c)
        {
            while (s[i] && s[i] != c && ++cnt)
                i++;
            strs[j] = ft_calloc(cnt + 1, sizeof(char));
            if (!strs[j])
                return NULL;
            j++;
        }
        while (s[i] && s[i] == c)
            i++;
    }
    return strs;
}

// fills the memory allocated with the substrings that has been parsed
// uses the same logic as that in ft_count
static char **ft_filler(char const *s, char c, char **strs)
{
    size_t i = 0, j = 0, k = 0;
    while (s[i] && strs[j])
    {
        if (s[i] != c)
        {
            k = 0;
            while (s[i] && s[i] != c)
                strs[j][k++] = s[i++];
            j++;
        }
        while (s[i] && s[i] == c)
            i++;
    }
    return strs;
}

// returns the pointer to the array of string pointers plus one for NULL terminator
// uses the helper functions above to do the same step by step
// the main function to be called
char **ft_split(char const *s, char c)
{
    size_t count;
    char **strs, **tofree;
    if (!s)
        return NULL;
    count = ft_count(s, c);
    strs = ft_calloc(count + 1, sizeof(char *));
    if (!strs)
        return NULL;
    if (!count)
        return strs;
    tofree = strs;
    strs = ft_allocator(s, c, strs);
    if (!strs)
        return (ft_free_char2(tofree), NULL);
    return ft_filler(s, c, strs);
}