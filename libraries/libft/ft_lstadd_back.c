#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *curr;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    curr = *lst;
    while (curr && curr->next)
        curr = curr->next;
    curr->next = new;
}