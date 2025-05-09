#include "libft.h"

// t_list **lst -> pointer to the pointer to the head of the linked list
// adds the new node to the end of the linked list
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