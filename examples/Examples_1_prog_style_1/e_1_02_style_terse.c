/***************************************************
    Example 1.2
    Demonstration of short-cut boolean 
    expressions in loop headers

/***************************************************/ 

#include <stdio.h>
#define MAXCHARS 100

int main (void)
{
    char line[MAXCHARS];

    // terse notation
    while (fgets(line, MAXCHARS, stdin))
    {
        puts(line);
        // block of code here
    }
    
    // verbose notation
    while (fgets(line, MAXCHARS, stdin) != NULL)
    {
        puts(line);
        // block of code here
    }

    return 0;
}

