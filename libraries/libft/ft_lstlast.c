#include "libft.h"

// returns the pointer to the last node of the linked list
t_list *ft_lstlast(t_list *lst)
{
    while (lst && lst->next)
        lst = lst->next;
    return lst;
}