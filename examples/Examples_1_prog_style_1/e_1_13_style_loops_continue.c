/***************************************************
    Example 1.13
    Demonstration of an acceptable use of the continue
    statement
        
/***************************************************/ 

#include <stdio.h>
#include <string.h>

int main (void)
{
    int iswhitespace(char s[]);
    int onlyletters(char s[]);
    char user_input[100];
        
    
    while (gets(user_input), strcmp(user_input, "quit"))  //  != 0
    {
        if (iswhitespace(user_input))
        {
            continue;
        }
        if (!onlyletters(user_input))
        {
            printf("Invalid characters!\n");
            continue;
        }
        // process user input here
        printf("%s", user_input);
    }
    return 0;
}

/***************************************************
    Checks if a string is all whitespace
*/ 
int iswhitespace(char s[])
{
    // code goes here
    return 0;
}

/***************************************************
    Checks if a string has non-letter characters
*/ 
int onlyletters(char s[])
{
    // code goes here
    return 0;
}
