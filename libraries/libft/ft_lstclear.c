#include "libft.h"

// t_list **lst -> pointer to th epointer to the head of the linked list
// void (*del)(void *) -> del function that takes a void pointer and returns a void pointer
// the del function is used to free the content of the node
// the function iterates through the linked list and frees each node and its contents using the del function
void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *next, *curr;
    if (!lst || !*lst || !del)
        return;
    curr = *lst;
    next = curr->next;
    while (curr && next)
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