/*********************************************************
    Examples: 4.5 Counting the number of sentences in a
    file with strpbrk
/*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIGLINE 1024
#define FILENAME "strpbrk.txt"

int main (void)
{
    int count_sentences(char *filename);
    int num_sentences;

    num_sentences = count_sentences(FILENAME);
    printf("\n\nYour file has %d sentences in it!\n", num_sentences);

    return 0;
}
/*************************************************************
  Counts the number of sentences in a file
*/
int count_sentences(char *filename)
{
    char line[BIGLINE]; // allow for very long lines
    char *mover;
    FILE *fp;
    int num_sentences = 0;

    if((fp = fopen(filename, "r")) == NULL)
    {
        printf("Failure to open input file! Aborting!\n");
        exit(1);
    }
    while (fgets(line, BIGLINE - 1, fp))
    {
        // fputs(line, stdout);
        for (mover = line; mover = strpbrk(mover, "?!."); mover++)
        {
            if (!isdigit(mover[1]))
            {
                num_sentences++;
                while(mover[1] == '?' || mover[1] == '!') mover++;
            }
        }
    }
    return num_sentences;
}
