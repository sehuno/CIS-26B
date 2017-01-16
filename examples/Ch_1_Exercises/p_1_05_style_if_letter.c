/***************************************************
    Exercise 1.5
    Rewrite the following program using optimal C coding style.
    Pay attention to:
    - white spaces and indentation
    - short-cut boolean expressions in if or loop statements
    - use the ternary operator
    - code redundancy
    - proper use of the relational expression in a return statement
    - use of the comma operator in a loop
    - use of && and || to prevent if nesting

    Name:
    Date:
/***************************************************/
#include <stdio.h>

int main (void)
{
    int checkLetter(char aChar);
    //char c = '*';
    //char c = 'a';
    char c = 'B';

    printf("%c is ", c);
    if (checkLetter(c) == 0)
        printf("not ");
    printf(" a letter\n");

    return 0;
}
/***************************************************
    Checks if a character is a letter or not
*/
int checkLetter(char aChar)
{
    int isLetter;

    if (aChar >= 'a' && aChar <= 'z')
        isLetter = 1;
    else
        if (aChar >= 'A' && aChar <= 'Z')
            isLetter = 1;
        else
            isLetter = 0;

    return isLetter;
}

/** SAVE THE OUTPUT BELOW

*/
