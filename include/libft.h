#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

// linked list for generic data storage
typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

int ft_isalpha(int c);                                                   // check if the character is alphabet
int ft_isdigit(int c);                                                   // check if the character is digit
int ft_isalnum(int c);                                                   // check if the character is alphanumeric
int ft_isascii(int c);                                                   // check if the character is ascii character
int ft_isprint(int c);                                                   // check if the character is printable
int ft_isspace(char c);                                                  // check if the character is a whitespace
int ft_toupper(int c);                                                   // convert to uppercase
int ft_tolower(int c);                                                   // convert to lowercase
size_t ft_strlen(const char *str);                                       // get the length of the string (excluding the null terminator)
size_t ft_strs_len(char **str);                                          // get the number of strings in a NULL-terminated array of strings
size_t ft_strs_arr_len(char ***str);                                     // get the number of arrays in a NULL-terminaed array of string arrays
void *ft_memset(void *b, int c, size_t len);                             // fills a block of memory wioth specified value
void ft_bzero(void *s, size_t n);                                        // fills a block of memory with zero
void *ft_memcpy(void *dest, const void *src, size_t n);                  // copies memory from src to dst (no overlap)
void *ft_memmove(void *dest, const void *src, size_t len);               // copies memory from src to dst (overlap allowed)
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);           // copies with null termination, of given length - 1
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);           // concatenates with null termination, of given length - 1
char *ft_strchr(const char *s, int c);                                   // returns pointer to fist occurence to specified character in a string
char *ft_strrchr(const char *s, int c);                                  // returns pointer to last occurence to specified character in a string
int ft_strcmp(const char *s1, const char *s2);                           // compares lexicographically two strings
int ft_strncmp(const char *s1, const char *s2, size_t n);                // compares lexicographically upto n characters
void *ft_memchr(const void *s, int c, size_t n);                         // searches the memory for the first occurence of the character
int ft_memcmp(const void *s1, const void *s2, size_t n);                 // compares two blocks of memory
char *ft_strnstr(const char *haystack, const char *needle, size_t len);  // finds the first occurence of needle in haystack
int ft_atoi(const char *str);                                            // string -> integer
int ft_atoi_base(const char *str, int base);                             // string -> integer of specified base
char *ft_itoa(int n);                                                    // integer->string conversion
void *ft_calloc(size_t count, size_t size);                              // calloc call for memory allotment
char *ft_strdup(const char *s1);                                         // duplicates a string
char *ft_substr(char const *s, unsigned int start, size_t len);          // returns a substring of s from start to len
char *ft_strjoin(char const *s1, char const *s2);                        // concatenates two strings
char *ft_strjoin_f(char *s1, char *s2);                                  // concatenates two strings and frees the first one
char *ft_strjoin_with(char const *s1, char const *s2, char c);           // concatenates two strings with a character in between
char *ft_strjoin_with_f(char *s1, char *s2, char c);                     // concatenates two strings with a character in between and frees the first one
char *ft_strtrim(char const *s1, char const *set);                       // trims the string s1 from the characters in set
char **ft_split(char const *s, char c);                                  // splits the string s into an array of strings using c as delimiter
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));          // applies a function to each character of the string
void ft_striteri(char *s, void (*f)(unsigned int, char *));              // applies a function to each character of the string with its index
void ft_putchar_fd(char c, int fd);                                      // writes a character to the file descriptor
void ft_putstr_fd(char *s, int fd);                                      // writes a string to the file descriptor
void ft_putendl_fd(char *s, int fd);                                     // writes a string to the file descriptor with a newline
void ft_putnbr_fd(int n, int fd);                                        // writes an integer to the file descriptor
t_list *ft_lstnew(void *content);                                        // creates a new list element
int ft_lstsize(t_list *lst);                                             // returns the size of the list
t_list *ft_lstlast(t_list *lst);                                         // returns the last element of the list
void ft_lstadd_front(t_list **lst, t_list *new);                         // adds a new element to the front of the list
void ft_lstadd_back(t_list **lst, t_list *new);                          // adds a new element to the back of the list
void ft_lstdelone(t_list *lst, void (*del)(void *));                     // deletes a single element of the list
void ft_lstclear(t_list **lst, void (*del)(void *));                     // deletes the entire list
void ft_lstiter(t_list *lst, void (*f)(void *));                         // applies a function to each element of the list
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)); // applies a function to each element of the list and returns a new list
void ft_free_char2(char **tofree);                                       // frees a NULL-terminated array of strings
void ft_free_char3(char ***tofree);                                      // frees a NULL-terminated array of string arrays

#endif /* LIBFT_H */