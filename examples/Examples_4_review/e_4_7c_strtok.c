/*********************************************************
    Examples: 4.7 strtok and convertion of user input
    to integer
/*********************************************************/

#include <stdio.h>
#include <stdlib.h> // strtol
#include <string.h> // strtok

int main (void)
{
    int tokennum, num;
    char line[256], *lineptr, *tokenptr, *endp;

    while (printf("\nEnter some integers: "), gets(line), strcmp(line, "quit"))
    {
        lineptr = line; // for the first token in line
        for (tokennum = 1; tokenptr = strtok(lineptr, "\040\t");
             lineptr = NULL, tokennum++) // lineptr = NULL for the rest for the tokens in the current line
        {
            num = (int) strtol(tokenptr, &endp, 10);
            if (*endp != '\0')
            {
                printf("   Token numner %d is not a valid integer\n", tokennum);
            }
            else
            {
                printf("   Token number %d is %d\n", tokennum, num);
            }
        }
    }
    return 0;
}
