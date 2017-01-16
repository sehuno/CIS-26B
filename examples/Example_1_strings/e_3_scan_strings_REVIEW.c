/* 
  
	reading strings using scanf

*/

#include <stdio.h>

#define FLUSH while( getchar() != '\n' )

int main (void)
{
/*  Local Definitions */

	char word_a[5];
	char word_b[5];

/*  Statements */

    /* read using %s */
    printf( "Please enter \"pseudocode\": " );
	scanf( "%s", word_b );
	printf( "***%s***\n\n", word_b );	

    printf( "Please enter \"main\": " );
    scanf( "%s", word_a );
    printf( "***%s***\n",   word_a );
    printf( "***%s***\n\n", word_b );

    /* read using %4s */
    printf( "Please enter \"pseudocode\": " );
    scanf( "%4s", word_b );
    printf( "***%s***\n\n", word_b );	

    printf( "Please enter \"main\": " );
    scanf( "%4s", word_a );
    printf( "***%s***\n",   word_a ); 
	printf( "***%s***\n\n", word_b );

    /* read using %4s and FLUSH */
    FLUSH;

    printf( "Please enter \"pseudocode\": " );
	scanf( "%4s", word_b );
    FLUSH;
	printf( "***%s***\n\n", word_b );	

	printf( "Please enter \"main\": " );
	scanf( "%4s", word_a );
    FLUSH;
	printf( "***%s***\n",   word_a );
	printf( "***%s***\n\n", word_b );

    return 0;

} /* main */
