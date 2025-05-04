#include "libft.h"

void *ft_calloc(size_t count, size_t size)
{
    void *temp;
    if (count == SIZE_MAX || size == SIZE_MAX)
        return NULL;
    temp = malloc(size * count);
    if (!temp)
        return NULL;
    return ft_memset(temp, 0, size * count);
}