/***************************************************
    Example 1.14
    Demonstration of an improper use of the feof
    function
        
/***************************************************/ 

#include <stdio.h>
#include <string.h>

int main (void)
{
    FILE *fpin = fopen("e_1_14b_style_feof.c", "r");
    char  line[100];

    while (!feof(fpin))
    {
        if(fgets(line, 100, fpin)) // != NULL
            fputs(line, stdout);
        
    }
    fclose(fpin);
    return 0;
} 
// Now it works...but the program is checking for EOF
// twice per iteration: UGLY!
