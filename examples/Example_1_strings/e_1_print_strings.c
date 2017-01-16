/* 
  
	printing one string 5 times: %s, %10s, %20s, %30s, %-20s

*/

#include <stdio.h>

int main (void)
{
/*  Local Definitions */

	char name[21] = "Victor Johnson";
	

/*  Statements */
	printf( "***%s***\n\n", name );

	printf( "***%10s***\n\n", name );  /* 10 ignored! */
		
	printf( "***%.5s***\n\n", name );

	printf( "***%20s***\n\n", name );

	printf( "***%30s***\n\n", name );

	printf( "***%-20s***\n\n", name );

    return 0;

} /* main */
