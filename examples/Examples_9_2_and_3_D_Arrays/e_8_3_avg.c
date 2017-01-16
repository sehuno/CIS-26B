/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  Calculate the average of all numbers in a 2D array
  
****************************************************************************/
#include <stdio.h>

#define ROWS 3
#define COLS 4

double calc_2Daverage(int a[][COLS], int rows, int cols);
double calc_average(int *ptr, int num_elem);
void print2D(int a[][COLS], int rows, int cols);

int main( void )
{      
    int a[ROWS][COLS] = 
    {
        {10, 10, 10, 10}, 
        {20, 20, 20, 20}, 
        {30, 30, 30, 30}
    };    
      
    print2D(a, ROWS, COLS);
    printf("\tAverage: %.2f\n", calc_2Daverage(a, ROWS, COLS));
    printf("\tAverage: %.2f\n", calc_average(&a[0][0], ROWS * COLS));

    print2D(a, 2, 2);
    printf("\tAverage: %.2f\n", calc_2Daverage(a, 2, 2));
    printf("\tAverage: %.2f INCORRECT!\n", calc_average(&a[0][0], 2 * 2)); // INCORRECT!!!

    return 0;
}

/********************************************************
   Calculate average of all elements in a 2D array
   Assume num_elem is not zero!
*/
double calc_2Daverage(int a[][COLS], int rows, int cols)
{
    int i, j, sum = 0;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            sum += a[i][j];        
    }
    return (double)sum / (rows * cols);
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
   Prints a 2D array
*/
void print2D(int a[][COLS], int rows, int cols)
{
    int i, j;

    putchar('\n');
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            printf("%3d ", a[i][j]);
        putchar('\n');
    }
    putchar('\n');
    return;
}
