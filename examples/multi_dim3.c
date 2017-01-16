#include <stdio.h>

int **calcSmall(int a[][ROWS][COLS], int tbls, int rows, int cols) 
{
	int **pSm;
	int t, r, c;
	pSm = (int **) calloc(tbls, sizeof(int *));
	if(!pSm) printf("Error!\n"), exit(111);

	for(t = 0; t < tbls; t++){
		pSm[t] = &a[t][0][0];
		for(r = 0; r < rows; r++)
			for(c = 0; c < cols; c++)
				if(a[t][r][c] > *pSm[t])
					pSm[t] = &a[t][r][c];
	}

	return pSm;
}