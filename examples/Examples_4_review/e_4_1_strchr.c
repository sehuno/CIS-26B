/*******************************************************
    Examples: 4.1 Using strchr and strrschr
/*******************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char s1[] = "I am the one, the only one.";
    char *ptr1, *ptr2;

    ptr1 = strchr(s1, 'o');
    ptr2 = strrchr(s1, 'o');

    printf("String starting at leftmost 'o' is: %s\n", ptr1);
    printf("String starting at rightmost 'o' is: %s\n", ptr2);

    // Fins all o's in s1; print their addresses and indices
    printf("Adress of beginning of s1 is: %p\n", s1);
    for (ptr1 = s1; (ptr1 = strchr(ptr1, 'o')) != NULL; ptr1++)
    {
        printf("Address of current 'o' is: %p\n", ptr1);
    }
    putchar('\n');
    // Change all o's to A's
    printf("Initial string: %s\n", s1);
    for (ptr1 = s1; (ptr1 = strchr(ptr1, 'o')) != NULL; ptr1++)
    {
        *ptr1 = 'A';
    }
    printf("    New string: %s\n", s1);


    return 0;
}
