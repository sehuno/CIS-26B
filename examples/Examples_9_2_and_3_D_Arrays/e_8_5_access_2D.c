/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  Accessing elements in a 2D array
  
****************************************************************************/
#include <stdio.h>

#define ROWS 3
#define COLS 4

void print2D(int a[][COLS], int rows, int cols);

int main( void )
{
    
    int a[ROWS][COLS] = 
    {//   0   1   2   3 
        {10, 20, 30},    // row 0
        {40, 50, 60},    // row 1
                         // row 2
    };
    
    print2D(a, 2, 3);
    print2D(a, ROWS, COLS);
    
    printf("a[0][3] = %3d\n",   a[0][3]);
    printf("a[0][4] = %3d\n",   a[0][4]);
    printf("a[0][5] = %3d\n\n", a[0][5]);
        
    printf("a[1][3] = %3d\n",   a[1][3]);
    printf("a[1][4] = %3d\n",   a[1][4]);
    printf("a[1][5] = %3d\n\n", a[1][5]);
    
    printf("a[2][3] = %3d\n",   a[2][3]);
    printf("a[2][4] = %3d\n",   a[2][4]);
    printf("a[2][5] = %3d\n\n", a[2][5]);

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

