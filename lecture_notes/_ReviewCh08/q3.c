#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 20
#define TBLS  5

int **smallestsForTable(int a[TBLS][ROWS][COLS], int tbls, int rows, int cols);
int main() 
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
    int i;
    int **ptr = smallestsForTable(a, 3, 2, 4);
    for(i = 0; i < 3; i++)
    	printf("%d\n", **(ptr + i));
	return 0;
}

int **smallestsForTable(int a[TBLS][ROWS][COLS], int tbls, int rows, int cols)
{
	int **ptr, i, j, k, smallest;
	ptr = (int **) malloc(tbls * sizeof(int *));

	for(i = 0; i < tbls; i++)
		for(j = 0; j < rows; j++)
			for(k = 0; k < cols; k++)
			{
				if(k == 0) {
					smallest = a[i][j][k];
					*(ptr + i) = &a[i][j][k];
				}
				else {
					if(a[i][j][k] < smallest) {
						smallest = a[i][j][k];
						*(ptr + i) = &a[i][j][k];
					}
				}
			}
	return ptr;
}