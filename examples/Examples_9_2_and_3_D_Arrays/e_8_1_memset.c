/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  Using memset

****************************************************************************/
#include <stdio.h>
#include <string.h>


int main( void )
{
    int i, j;
    // int a[3][4] = {0};
    int a[3][4];

    // memset(a, 0, 12 * sizeof (int)); // INCORRECT!!!
    // memset(&a[0][0], 0, 12 * sizeof (int));
    // memset(a[0], 10, 12 * sizeof (int));
    // memset(&a[0][0], 1, 12 * sizeof (int)); // ???

    for (i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++ )
            printf("%3d ", a[i][j]);
        putchar('\n');
    }
    return 0;
}

