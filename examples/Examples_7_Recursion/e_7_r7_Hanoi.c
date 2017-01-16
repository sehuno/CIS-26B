/****************************************************************************
**
** RECURSION                             TOWERS OF HANOI
**
********************************************************
  The Towers of Hanoi is a clasic recursion problem that is relatively
  easy to follow, is efficient, and uses no complex data structures.

  According to the legend, the monks in a remote mountain monastery knew
  how to predict when the world would end. They had a set of three
  diamond needles. Staked on the first diamond needle were 64 gold disks
  of decreasing size. The monks moved one disk to another needle each hour,
  subject to the following rules:

  1. Only one disk could be moved at a time.
  2. A larger disk must never be stacked above a smaller one.
  3. One and only one auxiliary needle could be used for the intermediate
     storage of disks.
****************************************************************************/

#include <stdio.h>
#include <math.h>

int main ( void )
{
    void moveOne ( char source, char dest );
    void hanoi   ( int n, char source, char aux, char dest );

    int n = 3;
    int moves;

    moves = (int) pow( 2, n ) - 1;
    printf( "\n\nTowers of Hanoi\n\n%5d disks\n%5d moves\n\n", n, moves );
	printf( "\n\nTowers of Hanoi\n\nStart\n\n"  );
    hanoi( n, 'S', 'A', 'D' );

    return 0;
}


/*******************************************************
 Prints one move: from source to destination
*/
void moveOne ( char source, char dest )
{
    printf( "\t%c -> %c\n", source, dest );
    return;
}

/*******************************************************
 Recursively move one disk from source to destination.
*/
void hanoi   ( int n, char source, char aux, char dest )
{
    if( n == 1 )
        moveOne( source, dest );
    else{
        hanoi( n - 1, source, dest, aux );
        moveOne( source, dest );
        hanoi( n - 1, aux, source, dest);
    }
    return;
}

