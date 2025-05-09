#include "libft.h"

// deleted the node in the list to which the *lst pointer points
// uses the del function to free the content of the node
void ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst || !del)
        return;
    del(lst->content);
    free(lst);
}