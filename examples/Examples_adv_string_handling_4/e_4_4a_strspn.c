/*******************************************************
    Examples: 4.4 Using strspn to search for the first
    character that is not in a given set
/*******************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char *digits = "0123456789";
    char s[10] = "04262011";
    char t[11] = "04/26/2011";
    char u[] = "a function with a strange name";
    int  i, j, k;

    // testing string s
    printf("%d\n", strspn(s, digits)); // 8
    if (strspn(s, digits) == strlen(s))
        printf("%s contains only digits!\n", s);
    else
        printf("%s does not contain only digits!\n", s);

    // testing string t
    printf("%d\n", strspn(t, digits)); // 2

    if ((i = strspn(t, digits)) == strlen(t))
        printf("%s contains only digits!\n", t);
    else
        printf("%s contains a non-digit character at index %d!\n", t, i);
    // testing u
    i = strspn(u, " aeiou");   // i = 2
    j = strspn(u, " \t\n");    // j = 0
    k = strspn(u, " acefghimnorstuw");  // k = 30
    printf("%d %d %d\n", i, j, k);
    return 0;
}

