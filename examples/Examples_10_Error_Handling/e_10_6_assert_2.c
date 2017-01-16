/****************************************************************************

   Demonstration of the assert function

****************************************************************************/
//#define NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main( void )
{
    int a[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int i = 10, r;
/*
    assert(0 <= i && i < 10);
    printf("%d\n", a[i]);
*/
    srand(time(NULL));
    for (i = 0; i < 25; i++)
    {
//        r = rand() % 12 - 1;
        r = rand() % 9; // range 0 to 8
        printf("r = %d\n", r);
        assert(0 <= r && r < 10);
        printf("-*- %d\n", a[r]);
    }

    return 0;
}
