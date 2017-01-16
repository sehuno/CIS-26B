/***************************************************
    Example 1.7
    Demonstration of the improper use of the 
    multi-way if statement
    
/***************************************************/ 

#include <stdio.h>

int main (void)
{
    int  score = 61;    
    char grade;

    if (score >= 60)
    {
        if (score >= 70)
        {
            if (score >= 80)
            {
                if (score >= 90)
                {
                    printf("Excellent job!\n");
                    grade = 'A';
                }
                else
                {
                    printf("Good job!\n");
                    grade = 'B';
                }
            }
            else
            {
                printf("Average job!\n");
                grade = 'C';
            }
        }
        else
        {
             printf("Poor job!\n");
             grade = 'D';
        }
    }
    else
    {
         printf("Failing job!\n");
         grade = 'F';
    }

    return 0;
}
