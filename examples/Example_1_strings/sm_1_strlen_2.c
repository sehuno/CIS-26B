/* 
  
	strlen
*/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char s[10] = "Monday";
    char t[]   = "Wednesday";
    char u[10] = "";
    char *p = s;
    char *q = t + 3; 

	
	
	printf("String s: [%s]\n", s);
	printf("String t: [%s]\n", t);
	printf("String u: [%s]\n", u);
	printf("String p: [%s]\n", p);
	printf("String q: [%s]\n", q);

	printf("\n");
	printf("strlen(s)     is %d\n", strlen(s));
	printf("strlen(p)     is %d\n", strlen(p));
	printf("strlen(s + 1) is %d\n", strlen(s + 1));
	printf("strlen(u)     is %d\n", strlen(u));
	printf("strlen(t)     is %d\n", strlen(t));
	printf("strlen(q)     is %d\n", strlen(q));
	
    return 0;

} 
