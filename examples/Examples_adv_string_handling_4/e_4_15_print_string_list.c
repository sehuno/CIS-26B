/**********************************
  Examples: 4.15
  Print a list of strings
***********************************/

#include <stdio.h>

int main(void)
{
	char *commands[] = {"copy",
                        "delete",
                        "print",
                        "move",
                        "display",
                        "rename",
                        "quit",
                        NULL};

	char **mover = commands;
	while (*mover)
	{
		puts(*mover );
        mover++;
	}

	return 0;
}

