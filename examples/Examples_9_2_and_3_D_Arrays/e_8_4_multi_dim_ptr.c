/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  Pointer arithmetic and multi-dimensional arrays
  
****************************************************************************/
#include <stdio.h>

#define BOXS 25
#define TBLS 12
#define ROWS  4
#define COLS  7


int main( void )
{
    int a[ROWS][COLS] = {0};
    int b[TBLS][ROWS][COLS] = {0};
    int d[BOXS][TBLS][ROWS][COLS] = {0};
    int *ptr;
    int r = 3;  // row #3
    int c = 5;  // col #5
    int t = 9;  // table #9
    int x = 22; // box #22

    // 2D arrays and pointer arithmetic
    ptr = &a[0][0];
    // a[r][c] = 99;
    *(ptr + r*COLS + c) = 99;
    printf("a[%d][%d] = %d\n", r, c, a[r][c]);

    // 3D arrays and pointer arithmetic
    ptr = &b[0][0][0];
    // b[t][r][c] = 99;
    *(ptr + t*ROWS*COLS + r*COLS + c) = 88;
    printf("b[%d][%d][%d] = %d\n", t, r, c, b[t][r][c]);

    // 4D arrays and pointer arithmetic
    ptr = &d[0][0][0][0];
    // d[x][t][r][c] = 99;
    *(ptr + x*TBLS*ROWS*COLS + t*ROWS*COLS + r*COLS + c) = 77;
    printf("d[%d][%d][%d][%d] = %d\n", x, t, r, c, d[x][t][r][c]);


    return 0;
}
