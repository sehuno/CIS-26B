/* 
  
	strlen
*/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char s[10];
    	
	printf("String s: [%s]\n", s); // junk
		
	printf("Enter the name of your favorite day in a week: ");
	fgets(s, sizeof(s), stdin);

	printf("\nString s: ***%s***\n", s); // it contains the new line
    *(s + strlen(s) - 1) = '\0';       // remove the new line
	printf("\nString s: ***%s***\n", s); 

	
    return 0;

} 
