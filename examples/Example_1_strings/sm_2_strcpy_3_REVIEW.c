/* 
  
	strncpy
*/

#include <stdio.h>
#include <string.h>

int main (void)
{
	char t[10];
	char s[10] = "Victor";
			
	printf("[%s] [%s]\n", s, t);
	//		[Victor] []

	// strncpy will not copy over the \0 and will show garbage values
	strncpy(t, s, 3);
	printf("[%s] [%s]\n", s, t);
	//		[Victor] [Vic_�]

	t[3] = '\0';
	printf("[%s] [%s]\n", s, t);
	//		[Victor] [Vic]

    return 0;

} 
