/*********************************************************
   CIS 26B -  Advanced C Programming
   Review Exercises: Multidimensional Arrays

   Write a function that returns a pointer to a row
   (the address of the row - NOT the address of its first element)
   that contains the smallest element in a table of ints.
   HINT: Use typedef!
/*********************************************************/

#include <stdio.h>

#define ROWS 10
#define COLS 20


int main(void)
{
    int a[ROWS][COLS] =
    {
        {70,  2, 30, 80, 50},
        {40, 60, 90, 50, 80},
        {80, 20, 60, 30, 90},
        {12, 10, 50, 20, 13}
    };
    int rows = 4, cols = 5;
    ???? rPtr;

    rPtr = calcSmall(a, rows, cols);
    printf( "The smallest element is found in row# %d\n", ????);

    return 0;

}
/************************************************************
*/
???? calcSmall(int table[][COLS], int rows, int cols)
{
    ???? rPtr = table;

    return rPtr;
}
