/***************************************************
    Example 1.8
    Demonstration of the proper use of the 
    multi-way if statement
    
/***************************************************/ 

#include <stdio.h>

int main (void)
{
    int  score = 88;    
    char grade;

    if (score >= 90)
    {
        printf("Excellent job!\n");
        grade = 'A';
    }
    else if (score >= 80)
    {
        printf("Good job!\n");
        grade = 'B';
    }
    else if (score >= 70)
    {
        printf("Average job!\n");
        grade = 'C';
    }
    else if (score >= 60)
    {
        printf("Poor job!\n");
        grade = 'D';
    }
    else
    {
         printf("Failing job!\n");
         grade = 'F';
    }

    // ...or use a switch statement
    score = 99;
    switch (score / 10)
    {
    case 10: 
    case 9: printf("Excellent job!\n");
            grade = 'A';
            break;
    case 8: printf("Good job!\n");
            grade = 'B';
            break;
    case 7: printf("Average job!\n");
            grade = 'C';
            break;
    case 6: printf("Poor job!\n");
            grade = 'D';
            break;
    default:printf("Failing job!\n");
            grade = 'F';
            break;
    }

    return 0;
}
