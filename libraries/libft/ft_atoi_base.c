#include "libft.h"

// return the decimal based on the base
static int base_digit(char c, int base)
{
    char *low, *up;
    int i;
    low = "0123456789abcdef";
    up = "0123456789ABCDEF";
    i = -1;
    while (++i < base)
        if (c == low[i] || c == up[i])
            return i;
    return -1;
}

// convert the string to an integer based on the base
int ft_atoi_base(const char *str, int base)
{
    size_t i;
    int sign;
    long int sum;
    if (!str)
        return 0;
    i = 0;
    while (ft_isspace(str[i]))
        i++;
    sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    sum = 0;
    while (base_digit(str[i], base) != -1)
    {
        sum = sum * base + base_digit(str[i], base);
        if (sum < 0)
            return ((sign != -1) * -1); // overflow handles -1 on +ve, 0 on -ve
        i++;
    }
    return (sum * sign);
}