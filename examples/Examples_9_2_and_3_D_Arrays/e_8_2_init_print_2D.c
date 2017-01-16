/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  Initializing and printing 2D arrays

  A 2D array is an array of 1D arrays!

****************************************************************************/
#include <stdio.h>

#define ROWS 3
#define COLS 4

void print2D(int a[][COLS], int rows, int cols);

int main( void )
{
    // int a[ROWS][COLS];
    int a[ROWS][COLS] = {0};


    // int a[ROWS][COLS] =
    // {
    //     {10, 10, 10, 10},
    //     {20, 20, 20, 20},
    //     {30, 30, 30, 30}
    // };


    // int a[ROWS][COLS] = {10, 10, 10, 10, 20, 20, 20, 20, 30, 30, 30, 30};


    // int a[ROWS][COLS] =
    // {
    //     {10},
    //     {20, 20},
    //     {30, 30, 30}
    // };


    print2D(a, ROWS, COLS);
    //print2D(a, 2, 2);
    //print2D(a, 3, 2);
    //print2D(a, 2, 3);
    //print2D(a, 3, 3);


    return 0;
}

/********************************************************
   Prints a 2D array
*/
void print2D(int a[][COLS], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            printf("%3d ", a[i][j]);
        putchar('\n');
    }
    putchar('\n');
    return;
}
