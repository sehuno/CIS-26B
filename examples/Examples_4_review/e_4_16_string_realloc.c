/******************************************************
  Examples: 4.16
  Reads lines from a file whose name is passed on
  the command line. These lines are placed into an array
  that grows dynamically via realloc()

*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POINTERS 5
#define MAXLINE 1024

#define FILENAME "in_16.txt"

//int main(int argc, char *argv[])
int main(void)
{
    char **line_ptrs, **mover, line[MAXLINE];
	FILE *fp;
	int arr_size = 0, i;

    //if( (fp = fopen(argv[1], "r")) == NULL )
    if( (fp = fopen( FILENAME, "r")) == NULL )
    {
		//printf ("File %s could not be opened!\n\n", argv[1]);
		printf ("File %s could not be opened!\n\n", FILENAME);
		exit(1);
    }
    if ((line_ptrs = (char **)malloc(POINTERS *sizeof (char *))) == NULL)
    {
        printf("Fatal malloc error!\n");
        exit(1);
    }
    mover = line_ptrs;
    while (fgets(line, MAXLINE - 1, fp))
    {
        if ((*mover = (char *)malloc(strlen(line) + 1)) == NULL)
        {
            printf("Fatal malloc error!\n");
            exit(2);
        }
        strcpy(*mover, line);

        if (++arr_size % POINTERS == 0) // Need more pointers!
        {
            if ((line_ptrs = (char **)realloc(line_ptrs, (arr_size + POINTERS) * sizeof (char *))) == NULL)
            {
                printf("Fatal realloc error!\n");
                exit(3);
            }
            mover = line_ptrs + arr_size - 1; // Essential!!!
        }
        mover++;
    }
    *mover = NULL; // Sentinel-> end of the pointer list

    for (mover = line_ptrs; *mover; mover++ )
	{
		printf ("%s", *mover );
	}
	return 0;
}

