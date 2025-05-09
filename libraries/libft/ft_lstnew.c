#include "libft.h"

// creates a new node for the list and returns the pointer to it
t_list *ft_lstnew(void *content)
{
    t_list *nn;
    nn = ft_calloc(1, sizeof(t_list));
    if (!nn)
        return NULL;
    nn->content = content;
    nn->next = NULL;
    return nn;
}