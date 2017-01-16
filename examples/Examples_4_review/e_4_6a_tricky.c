/*********************************************************
    Examples: 4.6a Tricky string formatting
/*********************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char s[] = "Tricky string formatting";
    int  n   = 5;

    printf("%.*s\n", n, s);
    printf("%.*s\n", n, s + 1);
    printf("%.*s\n", n, s + 8);

    // print n characters starting at the given address
    return 0;
}
