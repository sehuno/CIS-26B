/****************************************************************************
**
** Multidimensional Arrays
**
********************************************************

  2D arrays and pointers
  
****************************************************************************/
#include <stdio.h>

#define ROWS 3
#define COLS 4

typedef int ROW[5];

void print2D(int a[][COLS], int rows, int cols);
void print1D(int list[], int size);

ROW *fun (int);

int main( void )
{
    
    int a[ROWS][COLS] = 
    {//   0   1   2   3 
        {10, 20, 30},    // row 0
        {40, 50, 60},    // row 1
                         // row 2
    };

    int *ptr;
    int (*rPtr)[COLS]; // WHAT IS THIS???
    
    print2D(a, ROWS, COLS);

    printf("a        = %p\n", a);          
    printf("a[0]     = %p\n", a[0]);       
    printf("&a[0][0] = %p\n", &a[0][0]);   
    printf("&a[0]    = %p\n", &a[0]);      
    printf("\n");

    // print a row in a table
    print1D(a[0], COLS); //print1D(&a[0][0], COLS);
    print1D(a[1], COLS); //print1D(&a[1][0], COLS);
    printf("\n");
    
    // print elements in the first row using a pointer
    ptr = a[0];
    print1D(ptr, 2);
    ptr++;
    print1D(ptr, 2);
    ptr++;
    print1D(ptr, 2);
    printf("\n");
    

    // use a pointer to move to the next row in a table
    ptr = a[0];
    print1D(ptr, COLS);
    ptr += COLS;
    print1D(ptr, COLS);
    ptr += COLS;
    print1D(ptr, COLS);
    printf("\n");
    
    // same as above, but using a special type of pointer 
    rPtr = &a[0];
    print1D(*rPtr, COLS);
    rPtr++;
    print1D(*rPtr, COLS);
    rPtr++;
    print1D(*rPtr, COLS);
    printf("\n");


    return 0;
}

/********************************************************
   Prints a 1D array
*/
void print1D(int list[], int size)
{
    int i; 
  
    for (i = 0; i < size; i++)
        printf("%3d ", list[i]);
    putchar('\n');
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


