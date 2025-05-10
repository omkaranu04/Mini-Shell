#include "minishell.h"

/*
    returns 1 if the given char is a single/double quote
    returns 0 otherwise
*/
int ft_is_quote(char c)
{
    if (c == '\'' || c == '"')
        return 1;
    return 0;
}

/*
    determines if the given char is a separator in shell syntax
    the separators include:
    - && (logical AND)
    - whitespace (space, tab)
    - <> (input/output redirection)
    - | (pipe)
    - () (open/close parenthesis)
*/
int ft_is_separator(char *s)
{
    if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t' || *s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
        return 1;
    return 0;
}

/*
    function is used to skip over the whitespaces in a line
    advances the line pointer to the first non-whitespace char
*/
void ft_skip_spaces(char **line)
{
    while (**line && ft_isspace(**line))
        (*line)++;
}

/*
    the function identifies the quote char at the curr posiition
    and checks if there is a matching quote in thr rest of the string
    returns true if such quote exists, otherwise returns false
*/
bool ft_skip_quotes(char *line, size_t *i)
{
    char quote = line[*i];
    if (ft_strchr(line + *i + 1, quote))
    {
        (*i)++;
        while (line[*i] != quote)
            (*i)++;
        (*i)++;
        return true;
    }
    return false;
}

/*
    the function prints an error message to stderr, if an unclosed
    quote is encountered in a line
*/
void ft_print_quote_err(char c)
{
    ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
    ft_putchar_fd(c, 2);
    ft_putstr_fd("'\n", 2);
    g_minishell.exit_s = 258;
}