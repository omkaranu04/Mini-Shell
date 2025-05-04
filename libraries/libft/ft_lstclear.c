#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *next, *curr;
    if (!lst || !*lst || !del)
        return;
    curr = *lst;
    next = curr->next;
    while(curr && next)
    {
        del(curr->content);
        free(curr);
        curr = next;
        next = curr->next;
    }
    del(curr->content);
    free(curr);
    *lst = NULL;
}