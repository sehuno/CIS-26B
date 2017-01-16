/* 
  
	reading strings using fgets

*/

#include <stdio.h>
#include <string.h>

#define FLUSH while( getchar() != '\n' )

int main (void)
{
/*  Local Definitions */

	char name[10];
    char temp[10];
    char *ptr;
    	  
/*  Statements */

    printf( "Please enter \"Mary Johnson\": " );
    fgets( name, sizeof( name ), stdin );
    printf( "***%s***\n", name );	  

    scanf( "%s", temp );
    printf( "***%s***\n\n", temp );	  


    FLUSH;

    printf( "Please enter \"Mary Johnson\": " );
    fgets( name, sizeof( name ), stdin );
    FLUSH;                                 /* must be used when reading from the keyboard */
    printf( "***%s***\n", name );	  

    printf( "Please enter any word: " );
    scanf( "%s", temp );
    printf( "***%s***\n\n", temp );	  

    FLUSH;

    printf( "Please enter \"Mary Lee\": " );
	fgets( name, sizeof( name ), stdin );
    FLUSH;
	/* fflush( stdin ); */
    printf( "***%s***\n", name );	  

    ptr = name + strlen(name) - 1;
    if( *ptr == '\n' )
        *ptr = '\0';
    printf( "***%s***\n\n", name );	  

    return 0;

} /* main */
