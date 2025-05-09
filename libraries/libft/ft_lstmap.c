#include "libft.h"

// takes a pointer to a list head amd deletion function and then it calls
// the function to clear the list
static void *ft_handle_clr(t_list **head, void (*del)(void *))
{
    ft_lstclear(head, del);
    return NULL;
}

// creates a new list by applying the transformation function f to each element
// and then return the pointer to the head of the new list
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *head, *nlst;
    void *content;
    if (!lst || !f || !del)
        return NULL;
    content = f(lst->content);
    head = ft_lstnew(content);
    if (!head)
        return (del(content), ft_handle_clr(&head, del), NULL);
    nlst = head;
    lst = lst->next;
    while (lst)
    {
        content = f(lst->content);
        nlst->next = ft_lstnew(content);
        nlst = nlst->next;
        if (!nlst)
            return (del(content), ft_handle_clr(&head, del), NULL);
        lst = lst->next;
    }
    nlst->next = NULL;
    return head;
}