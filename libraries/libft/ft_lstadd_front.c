#include "libft.h"

void ft_lstadd_front(t_list **lst, t_list *new_node)
{
    new_node->next = *lst;
    *lst = new_node;
}