#include <stdlib.h>
#include <stdio.h>

#define COL 4
#define ROW 3

typedef int (*LINE)[COL];
LINE* rowOfSmallest(int table[ROW][COL]);
int main()
{
	int table[ROW][COL] = {
		{234, 24, 842, 32},
		{294, 75, 38, 239},
		{329, 83, 38, 324}
	};
	LINE smallestRow = rowOfSmallest(table);
	printf("%d\n", **smallestRow);
	return 0;
}

LINE rowOfSmallest(int table[ROW][COL])
{
	int i, j, smallest;
	LINE ptr;

	for(i = 0; i < ROW; i++) 
	{
		for(j = 0; j < COL; j++)
		{
			if(i == 0 && j == 0) {
				smallest = table[i][j];
				ptr = &table[i];
				continue;
			}
			if(table[i][j] < smallest) {
				smallest = table[i][j];
				ptr = &table[i];
			}
		}
	}
	return ptr;
}