/***************************************************
    Example 1.4
    Demonstration of the use of the ternary operator
                    ? :
    in a return

/***************************************************/ 

#include <stdio.h>

int main (void)
{
    int  palindrome(char s[]); 
    int  a = 10, b = 7;
    char s[20] = "tattarrattat";

    printf("a = %d      b = %d\n", a, b);
    // A
    // verbose . . .
    if (a > b)
        printf( "%d is the largest\n",  a);
    else
        printf( "%d is the largest\n",  b);

    // versus terse
    printf( "%d is the largest\n", a > b ? a : b );


    // B
    // verbose . . .
    if (palindrome(s)) // if (palindrome(s) != 0)
        printf( "%s is a palindrome\n",  s);
    else
        printf( "%s is not a palindrome\n",  s);

    // versus terse
    printf( "%s is %s a palindrome!\n", s, palindrome(s) ? "" : " not");

    return 0;
}

/***************************************************
    Check if its parameter is a palindrome
*/ 
int palindrome(char s[])
{
    // block of code here
    return 1;
}

/*
  Use the ternary operator ? : to avoid writing the 
  same statements twice.

  Do not abuse the use of ? : in tricky ways that might 
  compromise readability.

  The ternary operator ? : is underused, 
  but it is easily abused.
*/