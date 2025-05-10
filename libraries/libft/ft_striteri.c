#include "libft.h"

// this function is useful when you need to process each char of the string
// the function pointer takes in the character and its index
// this function modifies the string in place
void ft_striteri(char *s, void (*f)(unsigned int, char *))
{
    size_t i;
    if (!s || !f)
        return;
    i = 0;
    while (s[i])
    {
        f(i, &s[i]);
        i++;
    }
}