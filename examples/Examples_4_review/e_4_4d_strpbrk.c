/*********************************************************
    Examples: 4.4 Using both strcspn and strpbrk to search 
    for the first character that IS in a given set
/*********************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char u[] = "a function with a strange name";
    int  i;
    char *p;

    i = strcspn(u, " aeiou");   // i = 0
    p = strpbrk(u, " aeiou");   // *p is a
    printf("%d %c\n", i, *p);

    i = strcspn(u, " \t\n");    // i = 1
    p = strpbrk(u, " \t\n");    // *p is ' ' space
    printf("%d [%c]\n", i, *p);

    i = strcspn(u, "01234w");   // i = 11
    p = strpbrk(u, "01234w");   // *p is 'w'
    printf("%d %c\n", i, *p);
    
    return 0;
}

