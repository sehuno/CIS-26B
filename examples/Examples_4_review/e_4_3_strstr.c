/*******************************************************
    Examples: 4.3 Using strstr to find all instances of
    a substring within a string - no overlaping!!
/*******************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    int find_num_substrings(char *string, char *substring);

    int numfound;
    char a[] = "Mississippi is my sister state",
         b[] = "Nonsense",
         c[] = "banana anatomy",
         d[] = "Andy Andrews";

    // First Search
    numfound = find_num_substrings(a, "is");
    printf("The string \"is\" is in \"%s\" %d times.\n", a, numfound);

    // Second Search
    numfound = find_num_substrings(b, "is");
    printf("The string \"is\" is in \"%s\" %d times.\n", b, numfound);

    // Third Search
    numfound = find_num_substrings(c, "an");
    printf("The string \"an\" is in \"%s\" %d times.\n", c, numfound);

    // Fourth Search
    numfound = find_num_substrings(d, "an");
    printf("The string \"an\" is in \"%s\" %d times.\n", d, numfound);
    return 0;
}

/**********************************************************************
  Find all instances of a substring within a string - no overlaping!!
*/
int find_num_substrings(char *string, char *substring)
{
    int count = 0;

    while (string = strstr(string, substring))
    {
        count++;
        string += strlen(substring);
    }
    return count;
}

/**********************************************************************
  Find all instances of a substring within a string - no overlaping!!

int find_num_substrings(char *string, char *substring)
{
    int count = 0;
    int len = strlen(substring); // call strlen only once!

    while (string = strstr(string, substring))
    {
        count++;
        string += len;
    }
    return count;
}
*/
