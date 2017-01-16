/*****************************************************
  Examples: 4.14
  Using Commend Line Arguments:
  A demonstration of using and traversing command line
  arguments. These arguments are held in an array of
  pointer to char.
******************************************************/

#include <stdio.h>

int main( int argc, char *argv[]) // argc - count; argv - vector
{
    int i;
    char **mover;

    for (i = 0; i < argc; i++)
    {
        printf("Argument %d is %s\n", i, argv[i]);
    }
    printf("\n");
    for (mover = argv; *mover != NULL; mover++)
    {
        printf("Argument pointed at by mover is %s\n", *mover);
    }

	return 0;
}

