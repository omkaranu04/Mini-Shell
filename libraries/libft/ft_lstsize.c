#include "libft.h"

// returns the size of the linked list by traversing over it
int ft_lstsize(t_list *lst)
{
    int count = 0;
    while (lst)
    {
        lst = lst->next;
        count++;
    }
    return count;
}