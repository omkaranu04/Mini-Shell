#include "libft.h"

// t_list **lst -> pointer to the pointer to the head of the linked list
// adds the new node ot the start of the linked list
void ft_lstadd_front(t_list **lst, t_list *new)
{
    new->next = *lst;
    *lst = new;
}