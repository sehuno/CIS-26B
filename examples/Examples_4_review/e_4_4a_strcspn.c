/*******************************************************
    Examples: 4.4 Using strcspn to search for the first
    character that IS in a given set
/*******************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char u[] = "a function with a strange name";
    int  i, j, k;
    i = strcspn(u, " aeiou");   // i = 0
    j = strcspn(u, " \t\n");    // j = 1
    k = strcspn(u, "01234w");   // k = 11

    printf("%d %d %d\n", i, j, k);
    return 0;
}

