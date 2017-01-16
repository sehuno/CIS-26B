/***************************************************
    Example 1.6
    Demonstration of the use of the comma operator 
    in a loop conditional
    
/***************************************************/ 

#include <stdio.h>

int main (void)
{
    void  getfraction(int *pa, int *pb); 
    int   a, b;    

    // solution 1 
    printf("Enter integers (0 to stop)\n");
    getfraction(&a, &b);
    while (b != 0)
    {
        // lots of code here
        printf("-----> %d / %d is %d\n", a, b, a / b);
        getfraction(&a, &b);
    }
    printf("Done!\n\n");

    // solution 2 - using the comma operator
    printf("Enter integers (0 to stop)\n");
    while (getfraction(&a, &b), b != 0)
    {
        // lots of code here
        printf("-----> %d / %d is %d\n", a, b, a / b);
    }
    printf("Done!\n\n");
    
    return 0;
}

/***************************************************
    Get an integer from the user
*/ 
void  getfraction(int *pa, int *pb)
{
    char line[80];

    printf("Enter an integer: ");
    gets(line);
    sscanf(line, "%d %d", pa, pb);
    return;
}

/*
  Another C operator that is not properly appreciated 
  is the comma operator!  
  It is a highly abusable operator!
*/