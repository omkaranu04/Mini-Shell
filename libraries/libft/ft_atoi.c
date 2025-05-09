#include "libft.h"

// ocnvert the string to an integer in base 10
int ft_atoi(const char *str)
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
    while (ft_isdigit(str[i]))
    {
        sum = sum * 10 + (str[i] - '0');
        if (sum < 0)
            return ((sign != -1) * -1); // handling overflow, -1 on +ve, 0 on -ve
        i++;
    }
    return sum * sign;
}