/***************************************************
    Example 1.3
    Demonstration of the use of the ternary operator
                    ? :
    in a return

/***************************************************/ 

#include <stdio.h>

int main (void)
{
    int getmax( int a, int b);
    int i = 10, j = 5;

    printf("i = %d      j = %d\n", i, j);
    printf("The largest of i and j is: %d\n", getmax(i, j));

    return 0;
}

/***************************************************
    Returns the largest of the two parameters
 
int getmax(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
*/

/***************************************************
    Returns the largest of the two parameters
*/ 
int getmax(int a, int b)
{
    return a > b ? a : b;
}

/*
 Use the ternary operator ? : to avoid writing the 
 same statements twice.
*/