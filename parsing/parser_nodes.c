#include "minishell.h"

// maps the binary operator to its corresponding node type
t_node_type ft_get_node_type(t_token_type type)
{
    if (type == T_AND)
        return N_AND;
    if (type == T_OR)
        return N_OR;
    return N_PIPE;
}

// converts the redirection token in to pareser IO type enum
t_io_type ft_get_io_type(t_token_type type)
{
    if (type == T_LESS)
        return IO_IN;
    if (type == T_GREAT)
        return IO_OUT;
    if (type == T_DLESS)
        return IO_HEREDOC;
    return IO_APPEND;
}

// allocates and initializes a new AST node, of given type and returns a pointer to it
t_node *ft_new_node(t_node_type type)
{
    t_node *new_node = (t_node *)ft_calloc(1, sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->type = type;
    return new_node;
}

/*
    allocates and initializes a new IO redirection type node
    given the type and the value of the redirection
*/
t_io_node *ft_new_io_node(t_token_type type, char *value)
{
    t_io_node *new_node = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
    if (!new_node)
        return NULL;
    new_node->type = ft_get_io_type(type);
    new_node->value = ft_strdup(value);
    if (!new_node->value)
        return (free(new_node), NULL);
    return new_node;
}

// appends a new IO type node to the end of an IO list
void ft_append_io_node(t_io_node **lst, t_io_node *new)
{
    t_io_node *curr_node;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    curr_node = *lst;
    while (curr_node && curr_node->next)
        curr_node = curr_node->next;
    curr_node->next = new;
}