/***************************************************
    Exercise 1.2
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
    int countOdd(int a[], int n);
    int a[100] = { 1, 2, 3, 4, 5, 4, 3, 2, 1, 9};
    int n = 10;

    if (countOdd(a,n) != 0)
      if (countOdd(a,n) == 1)
        printf("%d odd number\n", countOdd(a, n));
      else
        printf("%d odd numbers\n", countOdd(a, n));
    else
      printf("No odd numbers\n");

    return 0;
}
/***************************************************
    Counts the odd elements in an arrays of ints
*/
int countOdd(int a[], int n)
{
    int i, count = 0;

    for (i = 0; i < n; i++)
        if (a[i]%2!= 0)
            count++;

    return count;
}

/** SAVE THE OUTPUT BELOW

*/

