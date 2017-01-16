/****************************************************************************

   Using Pointers to Functions as function arguments

****************************************************************************/
#include <stdio.h>
#include <string.h>

#define SIZE 103

int main( void )
{
    unsigned int RSHash(const char *key, int size);
    unsigned int DEKHash(const char *key, int size);
    unsigned int DJBHash(const char *key, int size);

    void printHash( const char *name, unsigned int (*hash)(const char *, int) );

    // define a pointer to a function
    //unsigned int (*hash)(const char *key, int size);

    printf("Address of RSHash : %p\n", RSHash);
    printf("Address of DEKHash: %p\n", DEKHash);
    printf("Address of DJBHash: %p\n\n", DJBHash);

    printHash( "RSHash", RSHash );
    printHash( "DEKHash", DEKHash );
    printHash( "DJBHash", DJBHash );

    return 0;
}
/**************************************************
   Print Hash
*/
void printHash(  const char *name, unsigned int (*hash)(const char *, int) )
{
    char key[] = "CIS 26B: Advanced C";
    //char key[] = "Advanced C";

    printf("%-12s: %u\n", name, hash(key, SIZE));
    return;
}


/**************************************************
   A simple hash function based on an example from
   Robert Sedgwicks Algorithms in C book.
*/
unsigned int RSHash(const char *key, int size)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   while (*key)
   {
      hash = hash * a + *key;
      a    = a * b;
      key++;
   }

   return hash % size;
}

/**************************************************
  A variation of an algorithm proposed by
  Donald E. Knuth in The Art Of Computer Programming
  Volume 3, under the topic of sorting and search
  chapter 6.4.
*/
unsigned int DEKHash(const char *key, int size)
{
   unsigned int hash = (unsigned int)strlen(key);

   while (*key)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ *key;
      key++;
   }

   return hash % size;
}


/**************************************************
   A variation of algorithm produced by Professor Daniel J.
   Bernstein and shown first to the world on the usenet
   newsgroup comp.lang.c.
*/
unsigned int DJBHash(const char *key, int size)
{
   unsigned int hash = 5381;

   while (*key)
   {
      hash = ((hash << 5) + hash) + *key;
      key++;
   }

   return hash % size;
}

/**
Address of RSHash : 004013F5
Address of DEKHash: 00401452
Address of DJBHash: 0040149C

RSHash      : 34
DEKHash     : 5
DJBHash     : 27

*/
