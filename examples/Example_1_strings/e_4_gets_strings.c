/* 
  
	reading strings using scanf, gets, and fgets

*/

#include <stdio.h>
#include <string.h>

#define FLUSH while( getchar() != '\n' )

int main (void)
{
/*  Local Definitions */

	char name[21];
    	  
/*  Statements */

    /* read using %s */
    printf( "Please enter \"Mary Johnson\": " );
	scanf( "%20s", name );            
    FLUSH;
	printf( "***%s***\n\n", name );	  
    /* reads one word only!!! */

	printf( "Please enter \"Mary Johnson\": " );
	gets( name );
	printf( "***%s***\n\n", name );       
	/* no overflow validation - not possible!!! */

    printf( "Please enter \"Mary Johnson\": " );
	fgets( name, sizeof( name ), stdin );
	printf( "***%s***\n\n", name );	  
    /* yes overflow validation, but the name is containing \n!!!  */

    printf( "Please enter \"Mary Johnson\": " );
	fgets( name, sizeof( name ), stdin );
    *(name + strlen(name) - 1 ) = '\0';    /* change \n to \0 */
	printf( "***%s***\n", name );	  
    
    return 0;

} /* main */
