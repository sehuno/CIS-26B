/***************************************************
    Example 1.11
    Demonstration of the use of good C syntax 
    with loops
        
/***************************************************/ 

#include <stdio.h>
#include <ctype.h> // isalpha

int main (void)
{
    FILE *fpout = fopen("out.txt", "w");
    int  c, linenum = 1;
    
    fprintf(fpout, "\n%-5d", linenum);
    while ((c = fgetc(stdin))!= EOF)
    {
        if (isalpha(c)) c += 2;
        fputc(c, fpout);
        if (c == '\n')
        {
            linenum++;
            fprintf(fpout, "\n%-5d", linenum);
        }        
    }
    fclose(fpout);
    return 0;
}

