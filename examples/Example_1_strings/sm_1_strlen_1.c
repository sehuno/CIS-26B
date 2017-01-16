/* 
  
	strlen
*/

#include <stdio.h>
#include <string.h>

int main (void)
{
	char s[10] = "Victor";
	
	
	printf("My name is %s\n", s);
	printf("sizeof(s) is %d\n", sizeof(s));
	printf("strlen(s) is %d\n", strlen(s));
	
    return 0;

} 
