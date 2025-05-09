#include "libft.h"

// count -> number of elements, size -> size of each element
// allocates memory for the array, and init all bytes ot 0 using ft_memset
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