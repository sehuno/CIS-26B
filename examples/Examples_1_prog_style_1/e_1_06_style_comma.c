/***************************************************
    Example 1.6
    Demonstration of the use of the comma operator 
    in a loop conditional
    
/***************************************************/ 

#include <stdio.h>

int main (void)
{
    void  getint(int *pi); 
    int   i;    

    // solution 1 
    printf("Enter integers (0 to stop)\n");
    getint(&i);
    while (i != 0)
    {
        // lots of code here
        printf("-----> %d\n", i);
        getint(&i);
    }
    printf("Done!\n\n");

    // solution 2 - using the comma operator
    printf("Enter integers (0 to stop)\n");
    while (getint(&i), i != 0)
    {
        // lots of code here
        printf("-----> %d\n", i);
    }
    printf("Done!\n\n");
    
    return 0;
}

/***************************************************
    Get an integer from the user
*/ 
void  getint(int *pi)
{
    char line[80];

    printf("Enter an integer: ");
    gets(line);
    sscanf(line, "%d", pi);
    return;
}

/*
  Another C operator that is not properly appreciated 
  is the comma operator!  
  It is a highly abusable operator!
*/