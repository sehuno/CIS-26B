/***************************************************
    Example 1.12
    Demonstration of a horrible use of the break
    statement
        
/***************************************************/ 

#include <stdio.h>
#include <ctype.h> // isalpha

int main (void)
{
    int num = 12345;
        
    // improper use of break
    while (1)
    {
        printf("%d\n", num);
        num /= 10;
        if (num == 0) break;    
        printf("------> Not Done!\n");
    }
    printf("DONE!\n\n");


    // the proper way
    num = 12345;    
    while (num)  // num != 0
    {
        printf("%d\n", num);
        num /= 10;
        printf("------> Not Done!\n");
    }
    printf("DONE!\n\n");

    return 0;
}

