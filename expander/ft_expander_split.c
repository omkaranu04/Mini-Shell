#include "minishell.h"

// move to the end on current word, skipping over quoted substrings
static void ft_skip_word(char const *s, size_t *i)
{
    char quotes;
    while (s[*i] && s[*i] != ' ')
    {
        if (s[*i] != '\'' && s[*i] != '"')
            (*i)++;
        else
        {
            quotes = s[(*i)++];
            while (s[(*i)] != quotes)
                (*i)++;
            (*i)++;
        }
    }
}

// allocates memory for each word in result array absed on length of each word
static char **ft_allocator(char const *s, char **strs)
{
    size_t start, i = 0, j = 0;
    while (s[i])
    {
        if (s[i] != ' ')
        {
            start = i;
            ft_skip_word(s, &i);
            strs[j] = ft_calloc(i - start + 1, sizeof(char));
            if (!strs[j])
                return NULL;
            j++;
        }
        while (s[i] && s[i] == ' ')
            i++;
    }
    return strs;
}

// fills the allocated memory with the words from the input string
static void ft_words_filler(const char *s, char **strs, size_t *i, size_t j)
{
    char quotes;
    size_t k = 0;
    while (s[(*i)] && s[(*i)] != ' ')
    {
        if (s[(*i)] != '\'' && s[(*i)] != '"')
            strs[j][k++] = s[(*i)++];
        else
        {
            quotes = s[(*i)++];
            strs[j][k++] = quotes;
            while (s[(*i)] != quotes)
                strs[j][k++] = s[(*i)++];
            strs[j][k++] = s[(*i)++];
        }
    }
}

// Iterates through the input string and fills each allocated word in strs using ft_words_filler.
static char **ft_filler(char const *s, char **strs)
{
    size_t i = 0, j = 0;
    while (s[i] && strs[j])
    {
        if (s[i] != ' ')
        {
            ft_words_filler(s, strs, &i, j);
            j++;
        }
        while (s[i] && s[i] == ' ')
            i++;
    }
    return strs;
}

// do the whole splitting process
char **ft_expander_split(char const *s)
{
    size_t i = 0, count = 0;
    char **strs, **tofree;
    if (!s)
        return NULL;
    i = 0, count = 0;
    while (s[i])
    {
        if (s[i] != ' ' && ++count)
            ft_skip_word(s, &i);
        while (s[i] && s[i] == ' ')
            i++;
    }
    strs = ft_calloc(count + 1, sizeof(char *));
    tofree = strs;
    strs = ft_allocator(s, strs);
    if (!strs || !count)
        return (ft_free_char2(tofree), NULL);
    return ft_filler(s, strs);
}