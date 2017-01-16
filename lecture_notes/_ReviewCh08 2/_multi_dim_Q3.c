/*********************************************************
   CIS 26B -  Advanced C Programming
   Review Exercises: Multidimensional Arrays

   Write a function that returns a dynamically allocated
   array of pointers to the smallest elements in each table
   of a 3D array of ints (one pointer per table).

/*********************************************************/

#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 20
#define TBLS  5

???? calcSmall(???????, int tbls, int rows, int cols);
int main(void)
{
    int a[TBLS][ROWS][COLS] =
    {
        {
            {70, 90, 30, 80},
            { 4, 60, 90, 50}
        }, // Table 0
        {
            {70, 90,  3, 80},
            {40, 60, 90, 50}
        }, // Table 1
        {
            {70, 90, 30, 80},
            {40, 60, 90,  5}
        }  // Table 2
    };
    int tbls = 3, rows = 2, cols = 4;
    ?????? pSm;
    int i;

    pSm = calcSmall(a, tbls, rows, cols);

    for (i = 0; i < tbls; i++)
        printf( "The smallest element in table#%d is %d\n", i, ???????);

    return 0;

}
/************************************************************
*/
????? calcSmall(???????, int tbls, int rows, int cols)
{
    ????? pSm;

    return pSm;
}
