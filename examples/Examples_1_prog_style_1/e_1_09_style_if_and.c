/***************************************************
    Example 1.9
    Demonstration of the use of && 
    to prevent if nesting
        
/***************************************************/ 

#include <stdio.h>

int main (void)
{
    int  a, b, c, d;
    
    a = b = c = d = 10;
    // using nested if statements: 
    // poor program readability
    if (a == b)
        if (b == c)
            if (c == d)
            {
                // do something in here
                printf("All equal\n");
            }

    // using && 
    if (a == b && b == c && c == d)
    {
         // do something in here
         printf("All equal\n");
    }

    return 0;
}
