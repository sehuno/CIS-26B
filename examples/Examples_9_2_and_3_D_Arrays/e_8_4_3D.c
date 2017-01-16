/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  Initializing and printing 3D arrays 
  Calculate the average

  A 3D array is an array of 2D arrays!
  
****************************************************************************/
#include <stdio.h>

#define TBLS 2
#define ROWS 3
#define COLS 4

void print3D(int a[][ROWS][COLS], int tables, int rows, int cols);
double calc_average(int *ptr, int num_elem);
double average3D(int a[][ROWS][COLS], int tables, int rows, int cols);

int main( void )
{
    //int a[TBLS][ROWS][COLS];
    //int a[TBLS][ROWS][COLS] = {100};
    
    int a[TBLS][ROWS][COLS] = 
    {   {   {10, 10, 10, 10}, 
            {20, 20, 20, 20}, 
            {30, 30, 30, 30}
        }, 
        {   {40, 70, 10, 40}, 
            {50, 80, 20, 50}, 
            {60, 90, 30, 60}
        } 
    };
    

    //int a[TBLS][ROWS][COLS] = {10, 10, 10, 10, 20, 20, 20, 20, 30, 30, 30, 30, 40, 70, 10, 40, 50, 80, 20, 50, 60, 90, 30, 60};        
    
    /*
    int a[TBLS][ROWS][COLS] = 
    {   
        {   
            {10}, 
            {20, 20}, 
            {30, 30, 30} 
        },
        {   
            {50, 60}, 
            {70}, 
            {80, 90} 
        }
    };
    */

    /*
    int a[TBLS][ROWS][COLS] = 
    {   
        {{10}, {20, 20}, {30, 30, 30} }, // Table 0
        {{50, 60}, {70}, {80, 90}     }  // Table 1
    };
    */
    
    // int a[TBLS][ROWS][COLS] = {{{10}, {20, 20}, {30, 30, 30}}, {{50, 60}, {70}, {80, 90}}};
    
    
    print3D(a, TBLS, ROWS, COLS);
    //print3D(a, 2, 2, 3);
    //print3D(a, 2, 2, 2);

    printf("\tAverage: %.2f\n", calc_average(&a[0][0][0], TBLS * ROWS * COLS));
    printf("\tAverage: %.2f\n", average3D(a, TBLS, ROWS, COLS));
    

    return 0;
}

/********************************************************
   Prints a 3D array
*/
void print3D(int a[][ROWS][COLS], int tables, int rows, int cols)
{
    int i, j, k;

    printf("Print a 3D Array: %d tables,\n"
           "each table has %d rows,\n"
           "each row has %d elements!\n\n", tables, rows, cols);
    for (i = 0; i < tables; i++)
    {
        printf("\tTable %2d: \n", i);
        for (j = 0; j < rows; j++)
        {
            for (k = 0; k < cols; k++)
                printf("\t%3d ", a[i][j][k]);
            putchar('\n');
        }
        putchar('\n');
    }
    printf("===================================\n");
    return;
}


/********************************************************
   Calculate average of all elements in a 
   multidimensional array
   Assume num_elem is not zero!
   NOTE: This function assumes that the array is full!
*/
double calc_average(int *ptr, int num_elem)
{
    int *end = ptr + num_elem;    
    int sum = 0;
    
    while (ptr < end)
    {
        sum += *ptr++;
    }

    return (double)sum / num_elem;
}

/********************************************************
   Prints a 3D array
*/
double average3D(int a[][ROWS][COLS], int tables, int rows, int cols)
{
    int i, j, k, sum = 0;
    
    for (i = 0; i < tables; i++)
    {
        for (j = 0; j < rows; j++)
        {
            for (k = 0; k < cols; k++)
                sum += a[i][j][k];
        }        
    }
    return (double)sum / (tables * rows * cols);
}
