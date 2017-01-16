/***************************************************
    Example 1.14
    Demonstration of an improper use of the feof
    function
        
/***************************************************/ 

#include <stdio.h>
#include <string.h>

int main (void)
{
    FILE *fpin = fopen("e_1_14a_style_feof.c", "r");
    char  line[100];
    
    while (!feof(fpin))
    {
        fgets(line, 100, fpin);
        fputs(line, stdout);
    }
    fclose(fpin);
    return 0;
} 
// Why is the last line displayed twice?
