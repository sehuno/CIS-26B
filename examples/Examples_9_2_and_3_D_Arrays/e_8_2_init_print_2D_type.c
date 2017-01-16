/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  Define a typedef for an array

****************************************************************************/
#include <stdio.h>

#define ROWS 3
#define COLS 4

typedef int TABLE[ROWS][COLS];

void print2D(TABLE a, int rows, int cols);

int main( void )
{

    TABLE a =
    {
        {10, 10, 10, 10},
        {20, 20, 20, 20},
        {30, 30, 30, 30}
    };

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
void print2D(TABLE a, int rows, int cols)
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
