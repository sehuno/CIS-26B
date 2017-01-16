/***************************************************
    Example 1.1
    This program does the following:

        1) Swaps two integers.
        2) Prints the values of the newly swapped
           integers.
        3) Adds the two integers.
        4) Prints the result of the addition

/***************************************************/ 

#include <stdio.h>

int main (void)
{
    void swap(int *pi, int *pj);
    int  add(int i, int j);
    int i = 5, j = 10;

	swap(&i, &j);
    printf("i = %d      j = %d\n", i, j);
    printf("The sum of i and j is: %d\n", add(i, j));
    return 0;
}

/***************************************************
    Swap the values of the two integer parameters
*/ 
void swap(int *pi, int *pj)
{
    int temp;

    temp = *pi;
    *pi  = *pj;
    *pj  = temp;
    return;
}

/***************************************************
    Calculate the sum of the two integer parameters
*/
int add(int i, int j)
{
    return i + j;
}
