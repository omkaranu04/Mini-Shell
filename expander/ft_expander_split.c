#include "minishell.h"

/*
    advances an index past one word in the input string, stopping at a space
    or end of string but skipping over entire quoted segments
*/
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

/*  
    allocates the array of c strings needed to hold each word
*/
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

/*
    copies the actual characters of one word into its buffer, again respecting the quotes
    i.e. copies quotes also if they are present at the start and end of the word
*/
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

/*
    iterates over the input and the allocated string pointers in parallel
    and calling the ft_words_filler to fill in the next buffer
*/
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

/*
    top level entry point
    counts how many number of words appear by calling the ft_skip_words
    allocated the array of that many pointers + a NULL pointer
    calls the ft_allocator to allocate each word buffer
    calls the ft_filler to copy each word to its buffer
    returns the NULL terminates array of words
*/
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