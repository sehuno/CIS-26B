/* 
  
	printing 3 strings

*/

#include <stdio.h>

int main (void)
{
/*  Local Definitions */

  	char name_a[11] = "Victor";
	char name_b[11] = "Mary";
	char name_c[11] = "Sabrina";
	int  score_a    =  80;
	int  score_b    =  90;
	int  score_c    =  70;

/*  Statements */
	printf( "%s %d\n", name_a, score_a );
	printf( "%s %d\n", name_b, score_b );
    printf( "%s %d\n", name_c, score_c);
	printf( "\n\n" );

	printf( "%10s %4d\n", name_a, score_a );
	printf( "%10s %4d\n", name_b, score_b );
    printf( "%10s %4d\n", name_c, score_c );
	printf( "\n\n" );

	printf( "%-10s %4d\n", name_a, score_a );
	printf( "%-10s %4d\n", name_b, score_b );
    printf( "%-10s %4d\n", name_c, score_c );
	printf( "\n\n" );
	
    return 0;

} /* main */

