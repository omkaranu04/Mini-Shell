#include "minishell.h"

// creates a new token of the desired type and returns the pointer to the same
t_token *ft_new_token(char *value, t_token_type type)
{
    t_token *new_token = (t_token *)ft_calloc(1, sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->value = value;
    return new_token;
}

// adds the given new token to the end of the tokens list
// implemented as doubly linked list
void ft_token_list_add_back(t_token **lst, t_token *new_token)
{
    t_token *curr_node;
    if (!*lst)
    {
        *lst = new_token;
        return;
    }
    curr_node = *lst;
    while (curr_node && curr_node->next)
        curr_node = curr_node->next;
    curr_node->next = new_token;
    new_token->prev = curr_node;
}

// clears the given list, frees its content as well as the list structure
void ft_clear_token_list(t_token **lst)
{
    t_token *curr_node, *next;
    curr_node = *lst;
    if (!curr_node)
        return;
    while (curr_node)
    {
        free(curr_node->value);
        next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }
    *lst = NULL;
}