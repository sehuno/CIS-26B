/***************************************************
    Exercise 1.3
    Rewrite the following program using optimal C coding style.
    Pay attention to:
    - white spaces and indentation
    - short-cut boolean expressions in if or loop statements
    - use the ternary operator
    - code redundancy
    - proper use of the relational expression in a return statement
    - use of the comma operator in a loop
    - use of && and || to prevent if nesting


    Name:
    Date:
/***************************************************/
#include <stdio.h>

int main (void)
{
    int findMin(int a, int b, int c, int d);
    //int a = 10, b = 20, c = 5, d = 7;
    int a = 10, b = 2, c = 5, d = 7;

    printf("%d %d %d %d\n", a, b, c, d);
    printf("The smallest value is %d\n", findMin(a, b, c, d));

    return 0;
}
/***************************************************
    Find smallest
*/
int findMin(int a, int b, int c, int d)
{
    int min;

    if (a <= b && a <= c && a <= d )
        min = a;
    if (b <= a && b <= c && b <= d )
        min = b;
    if (c <= a && c <= b && c <= d )
        min = c;
    if (d <= a && d <= b && d <= c )
        min = d;
    return min;
}

/** SAVE THE OUTPUT BELOW

*/

