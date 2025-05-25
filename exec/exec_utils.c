#include "minishell.h"

/*
    helper function to free the pointer 
    and set it to NULL
*/
static void ft_del(void *ptr)
{
    free(ptr);
    ptr = NULL;
}

/*
    maintains a static linked list of pointers
    when clean is true it clears the entire garbage list using the ft_lstclear function
    else it adds the provided pointer to the garbage list and returning the same pointer
*/
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
        ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
        return ptr;
    }
}

/*
    function is used to compare a string against a delimiter pattern
    it returns true if all non-quote chars in delimiter matched str and there are no non-quote
    chars left in delimiter
*/
bool ft_is_delimiter(char *delimiter, char *str)
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