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

/* output:
Address of b is: 0x7fff5d658a0d
Address of c is: 0x7fff5d658a1c
Address of d is: 0x7fff5d658a06
Address of a in b is: 0x7fff5d658a0d
Address of a in c is: 0x7fff5d658a1f
Address of a in d is: 0x0
Search for "cat" in "cattle"
FOUND!: cattle
Search for "cat" in "concatenate"
FOUND!: catenate
Search for "cat" in "foobar"
NOT FOUND
*/
