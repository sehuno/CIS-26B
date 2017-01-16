/**********************************
  Examples: 4.15
  Create a ragged array of strings
  Each string contains a frame of
  size 14 x 69

***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define FILENAME "t0.txt"
#define FILENAME "t1.txt"
//#define FILENAME "t2.txt"
//#define FILENAME "t3.txt"

#define COLS 69
#define ROWS 14

int main(void)
{
	FILE *fpMovie;
	char *list[3500], **mover;
	char line[COLS];
	char tempFrame[ROWS * COLS] = "";
	int j;

    fpMovie = fopen( FILENAME, "r" );
	if( !fpMovie )
		printf ("Error opening the input file\n" ), exit(101);

	j = 0;
	mover = list;
	while ( fgets( line, sizeof(line) , fpMovie ) )
	{
		strcat(tempFrame, line);
		j++;
		if (j == ROWS) // done reading one frame
		{
			*mover = (char *) malloc( strlen(tempFrame) + 1);
			if (!(*mover))
				printf( "Not enough memory\n" ), exit(202);

            //strcpy(list[i], tempFrame);
            strcpy(*mover, tempFrame);
            *tempFrame = '\0';
			j = 0;
			mover++;
		}
	}
	*mover = NULL; // end of the pointer list
	fclose( fpMovie );

    for (mover = list; *mover; mover++ )
	{
		for (j = 0; j < 100; j++)
			printf("\n");

		printf ("%s", *mover );
        getchar();
	}
	return 0;
}

