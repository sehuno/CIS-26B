#include <stdio.h>

typedef int (*ROWPTR) [COLS];

ROWPTR rPtr;

// calling statement
rPtr = calcSmall(a, rows, cols);

ROWPTR calcSmall(int table[][COLS], int rows, int cols) 
{
	int r, c, sm = table[0][0];
	ROWPTR rPtr = table;

	for(r = 0; r < rows; r++) 
	{
		for(c = 0; c < cols; c++)
		{
			if(table[r][c] < sm)
			{
				sm = table[r][c];
				rPtr = &table[r];
			}
		}
	}
	return rPtr;
}