/***************************************************
    Exercise 1.4
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
    int checkTriangle(double a, double b, double c);
    double a = 10, b = 2, c = 3;
    //double a = 10, b = 20, c = 15;

    printf("%.1f %.1f %.1f are ",a,b,c);
    if (checkTriangle(a,b,c)==0)
        printf("not ");
    printf("the sides of a triangle!\n");

    return 0;
}
/***************************************************
    Checks if a, b, and c are the sides of
    a triangle
*/
int checkTriangle(double a, double b, double c)
{
    int check;

    if (a > 0)
        if (b > 0)
            if (c > 0)
                if (a < b + c)
                    if (b < a + c)
                        if (c < a + b)
                            check = 1;
                        else
                            check = 0;
                    else
                        check = 0;
                else
                    check = 0;
            else
                check = 0;
        else
            check = 0;
    else
        check = 0;
    return check;
}

/** SAVE THE OUTPUT BELOW

*/

