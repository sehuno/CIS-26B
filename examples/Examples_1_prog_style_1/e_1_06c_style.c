/***************************************************
    Example 1.6
    No comma operator needed
    
/***************************************************/ 

#include <stdio.h>

int main (void)
{
    int getint(void);       //void  getint(int *pi); 
    int   i;    

    // solution 1 
    printf("Enter integers (0 to stop)\n");
    i = getint();           //getint(&i);
    //while (i != 0)
    while (i)
    {
        // lots of code here
        printf("-----> %d\n", i);
        i = getint();       // getint(&i);         
    }
    printf("Done!\n\n");

    // solution 2 - using the comma operator
    printf("Enter integers (0 to stop)\n");
    //while ((i = getint()) != 0)
    while (i = getint())
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
//void  getint(int *pi)
int getint(void)
{
    char line[80];
    int i;

    printf("Enter an integer: ");
    gets(line);
    sscanf(line, "%d", &i);
    return i;
}

/*
  Use return to pass back only one value!
*/