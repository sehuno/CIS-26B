/*******************************************************
    Examples: 4.2 Using strstr
/*******************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char a[] = "cat", b[] = "cattle",
         c[] = "concatenate", d[] = "foobar";
    char *ptr;

    printf("Address of b is: %p\n\
            Address of c is: %p\n\
            Address of d is: %p\n\
            Address of a in b is: %p\n\
            Address of a in c is: %p\n\
            Address of a in d is: %p\n", b, c, d,
                                         strstr(b, a),
                                         strstr(c, a),
                                         strstr(d, a));
    // First Search
    printf("Search for \"%s\" in \"%s\"\n", a, b);
    if ((ptr = strstr(b, a)) != NULL)
    {
        printf("FOUND!: %s\n", ptr);
    }
    else
        printf("NOT FOUND");

    // Second Search
    printf("Search for \"%s\" in \"%s\"\n", a, c);
    if ((ptr = strstr(c, a)) != NULL)
    {
        printf("FOUND!: %s\n", ptr);
    }
    else
        printf("NOT FOUND");

    // Third Search
    printf("Search for \"%s\" in \"%s\"\n", a, d);
    if ((ptr = strstr(d, a)) != NULL)
    {
        printf("FOUND!: %s\n", ptr);
    }
    else
        printf("NOT FOUND");

    return 0;
}
