/***************************************************
    Example 1.5
    Demonstration of proper use of a relational 
    expression in a return statement
    
/***************************************************/ 

#include <stdio.h>

int main (void)
{
    int  check(int a, int b); 
    int  a = 10, b = 7;    

    printf("first = %2d\t second = %2d\t result = %d\n", a, b, check(a, b));
    printf("first = %2d\t second = %2d\t result = %d\n", b, a, check(b, a));
    
    return 0;
}

/***************************************************
    Returns 1 if the first parameter is greater than
    the second, 0 otherwise

    Solution 1: improper 

int  check(int a, int b)
{
    if( a > b )
        return 1;
    else
        return 0;
}
*/

/***************************************************
    Returns 1 if the first parameter is greater than
    the second, 0 otherwise

    Solution 2: proper
*/ 
int  check(int a, int b)
{
    return a > b;
}

/*
    Boolean return values from functions and Boolean 
    expressions are often misused.
*/