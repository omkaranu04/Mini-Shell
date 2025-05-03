#include "minishell.h"

// frees all the nodes in the io redirection list
void ft_clear_io_list(t_io_node **lst)
{
    t_io_node *curr_node, *next;
    curr_node = *lst;
    if (!curr_node)
        return;
    while (curr_node)
    {
        free(curr_node->value);
        ft_free_char2(curr_node->expanded_value);
        next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }
    *lst = NULL;
}

// clears a single command node
void ft_clear_cmd_node(t_node *node)
{
    if (!node)
        return;
    ft_clear_io_list(&(node->io_list));
    free(node->args);
    ft_free_char2(node->expanded_args);
}

// clears the entire AST recursively
void free_recursive_clear_ast(t_node *node)
{
    if (!node)
        return;
    if (node->type == N_CMD)
        ft_clear_cmd_node(node);
    else
    {
        if (node->left)
            free_recursive_clear_ast(node->left);
        if (node->right)
            free_recursive_clear_ast(node->right);
    }
    free(node);
}

// clears the entire AST and sets the pointer to NULL
void ft_clear_ast(t_node **ast)
{
    ft_recursive_clear_ast(*ast);
    *ast = NULL;
    ft_clear_token_list(&g_minishell.tokens);
}