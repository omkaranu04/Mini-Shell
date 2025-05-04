#include "libft.h"

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