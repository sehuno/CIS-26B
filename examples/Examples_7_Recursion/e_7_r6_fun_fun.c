/**************************************
   Example: fun - 2 recursive calls
*/

#include <stdio.h>

int main ( void )
{
    void fun ( int );
    fun( 3 );

    return 0;
}

/************************************/
void fun ( int n )
{
    if( n > 0 )
    {
        fun( n - 1 );
        printf( " %d\n", n );
        fun( n - 1 );
    }
    return;
}
