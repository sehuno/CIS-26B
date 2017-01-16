/* 
  
	strcpy
*/

#include <stdio.h>
#include <string.h>

int main (void)
{
	char s[10] = "Victor";
	char t[10];

    //t = s; // Does not work! Why?

	printf("\nBefore\n");
	printf("String s: [%s]\n", s);  // Victor
	printf("String t: [%s]\n", t);  // junk
	strcpy(t, s);

	printf("\nAfter\n");
	printf("String s: [%s]\n", s);  // Victor
	printf("String t: [%s]\n", t);  // Victor
	
    return 0;

} 
