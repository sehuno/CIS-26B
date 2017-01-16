#include <stdio.h>
int main (void) 
{
	// Check if value is odd
	int isLetter;
	char aChar = 's';
	int val = 1;
	if(val % 2 != 0)
		printf("Value is odd\n");

	// Check if character is character
	if (aChar >= 'a' && aChar <= 'z')
        isLetter = 1;
    else
        if (aChar >= 'A' && aChar <= 'Z')
            isLetter = 1;
        else
            isLetter = 0;

}