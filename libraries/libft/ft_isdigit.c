#include "libft.h"

// return if the given character is an digit or not
int ft_isdigit(int c)
{
    if ((c >= '0' && c <= '9'))
        return 1;
    return 0;
}
