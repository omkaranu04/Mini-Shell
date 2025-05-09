#include "libft.h"

// return if the character is a digit or an alphabet
int ft_isalnum(int c)
{
    if (ft_isalpha(c) || ft_isdigit(c))
        return 1;
    return 0;
}