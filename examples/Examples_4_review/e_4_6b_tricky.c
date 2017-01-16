/*********************************************************
    Examples: 4.6 Tricky string parsing with the
    string.h functions: Print the part of the string
    between the first two '#' characters.
/*********************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char line[80], *ptr1, *ptr2;

    while (gets(line), strcmp(line, "quit"))
    {
        ptr1 = strchr(line, '#');
        if (ptr1)
        {
            ptr1++; // skip the first '#'
            ptr2 = strchr(ptr1, '#');
        }
        if (!ptr1 || !ptr2)
        {
            printf("Line doesn't have two '#' characters!\n");
            continue;
        }
        printf("%.*s\n\n", ptr2 - ptr1, ptr1);
        // print (ptr2 - ptr1) characters beginning with *ptr1
    }

    return 0;
}
