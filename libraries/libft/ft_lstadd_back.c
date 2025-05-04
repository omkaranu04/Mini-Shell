#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new_node)
{
    t_list *curr;
    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    curr = *lst;
    while (curr && curr->next)
        curr = curr->next;
    curr->next = new_node;
}