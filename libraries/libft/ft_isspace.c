#include "libft.h"

// return if the character is a space
/*
    \t -> tab
    \n -> new line
    \v -> vertical tab. Moves the cursor down to the next line at the same horizontal position
    \f -> form feed. Page break character, originally used to advance paper to the top of the next page in printers
    \r -> carriage return. Moves the cursor to the beginning of the current line without advancing to the next line

*/
int ft_isspace(char c)
{
    if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
        return 1;
    return 0;
}