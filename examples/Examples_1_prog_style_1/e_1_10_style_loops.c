/***************************************************
    Example 1.10
    Demonstration of the use of bad C syntax 
    with loops - nested loops not needed!
        
/***************************************************/ 

#include <stdio.h>
#include <ctype.h> // isalpha

int main (void)
{
    FILE *fpout = fopen("out.txt", "w");
    int  c, linenum = 1;
    
    c = 'X';
    while (c != EOF)
    {
        fprintf(fpout, "\n%-5d", linenum);
        linenum++;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
            if (isalpha(c)) c += 2;
            fputc(c, fpout);
        }
        if (c != EOF)
        {
            fputc(c, fpout); // write the new line
        }
    }
    fclose(fpout);
    return 0;
}

