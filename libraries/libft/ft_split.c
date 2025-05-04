#include "libft.h"

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