/***************************************************
    Example 1.14
    Demonstration of a proper use of the feof
    function
        
/***************************************************/ 

#include <stdio.h>
#include <string.h>

int main (void)
{
    FILE *fpin = fopen("e_1_14c_style_feof.c", "r");
    char  line[100];

    // before using feof() you MUST READ from file
    fgets(line, 100, fpin);                    
    while (!feof(fpin))
    {
        fputs(line, stdout);
        fgets(line, 100, fpin);                    
    }
    fclose(fpin);
    return 0;
} 
// better, but WHY CALL TWO FUNCTIONS per iteration?
