/* 
  
	strcpy
*/

#include <stdio.h>
#include <string.h>

int main (void)
{
	char t[7] = "Victor";
	char s[3] = "Jo";
	
	printf("%p %p\n", s, t);

 // 	printf("[%s] [%s]\n", s, t);
	// strcpy(t, s);
	// printf("[%s] [%s]\n", s, t);


	// NOTE: SHOWS MEMORY OVERWRITTEN WHEN USING STRCPY INCORRECTLY
	printf("[%s] [%s]\n", s, t);
	strcpy(s, t);
	printf("[%s] [%s]\n", s, t);

	// printf("[%s] [%s]\n", s, t);
	// strncpy(s, t, sizeof(s) - 1);
	// printf("[%s] [%s]\n", s, t);

	
    return 0;

} 
