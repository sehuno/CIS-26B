/***************************************************
    Example 1.14
    Demonstration of a proper way of reading strings 
    from a text file: NO NEED to use the feof 
    function!
        
/***************************************************/ 

#include <stdio.h>
#include <string.h>

int main (void)
{
    FILE *fpin = fopen("e_1_14d_style_feof.c", "r");
    char  line[100];

    while (fgets(line, 100, fpin)) // != NULL
    {
        fputs(line, stdout);      
    }
    fclose(fpin);
    return 0;
} 
// The BEST!
