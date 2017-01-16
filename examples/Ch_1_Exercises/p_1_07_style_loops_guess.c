/***************************************************
    Exercise 1.7
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

int main(void)
{
    int guess(int  x, int  y);
    int x, y;

    for (x = 10, y = 20; x < 15; x++, y+=10)
        printf("%d\t%d\t\t%d\n", x, y, guess(x, y));

    return 0;
}

/***************************************************
    Guess what does this function calculate
*/
int guess(int  x, int  y)
{
    int sum=0; while (x!=0){if(x%2!=0)sum=sum+y;x=x/2;y=y*2;}
    return sum;
}

/** SAVE THE OUTPUT BELOW

*/
