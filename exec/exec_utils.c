#include "minishell.h"

// helper function to free a pointer
static void ft_del(void *ptr)
{
    free(ptr);
    ptr = NULL;
}

// garbage collector for memory management
// manages a static list of allocated pointers for bulk cleanup
void *ft_garbage_collector(void *ptr, bool clean)
{
    static t_list *garbage_list;
    if (clean)
    {
        ft_lstclear(&garbage_list, ft_del);
        return NULL;
    }
    else
    {
        ft_lsadd_back(&garbage_list, ft_lstnew(ptr));
        return ptr;
    }
}

// checks if a string is matches a delimiter, ignoring the quotes in the delimiter
int ft_is_delimiter(char *delimiter, char *str)
{
    while (*str)
    {
        if (*delimiter == '"' || *delimiter == '\'')
        {
            delimiter++;
            continue;
        }
        else if (*str == *delimiter)
        {
            str++;
            delimiter++;
        }
        else
            return false;
    }
    while (*delimiter == '"' || *delimiter == '\'')
        delimiter++;
    return (!*delimiter);
}