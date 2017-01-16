/****************************************************************************

   An array of pointers to functions

****************************************************************************/
#include <stdio.h>
#include <string.h>

#define SIZE 103

int main( void )
{
    unsigned int RSHash(const char *key, int size);
    unsigned int DEKHash(const char *key, int size);
    unsigned int DJBHash(const char *key, int size);

    void printHash( const char *name, unsigned int (*hash)(const char *key, int size) );


    unsigned int (*hashList[4])(const char *, int)  //define an array of pointers to functions
                     = {RSHash, DEKHash, DJBHash, NULL};
    unsigned int (**mover)(const char *key, int size) = hashList;      //define a pointer to a pointer to a function

    char *hashName[] = {"RSHash", "DEKHash", "DJBHash"};
    char **moverN;
    int i, n = 3;

    // Use an INDEX to print the address of each function in the list
    for (i = 0; i < n; i++)
        printf("%p\n", hashList[i]);
    printf("\n");

    // Use a POINTER to print the address of each function in the list
    for (mover = hashList; *mover; mover++)
        printf("%p\n", *mover);
    printf("\n");
     printf("\n");

    // Use an INDEX to call the printHash function
    for (i = 0; i < n; i++)
        printHash( hashName[i], hashList[i] );
    printf("\n");

    // Use POINTERS to call the printHash function
    for (mover = hashList, moverN = hashName; *mover; mover++, moverN++)
        printHash( *moverN, *mover );
    printf("\n");

    return 0;
}
/**************************************************
   Print Hash
*/
void printHash(  const char *name, unsigned int (*hash)(const char *, int) )
{
    char key[] = "CIS 26B: Advanced C";
    //char key[] = "Advanced C";

    printf("%p %-12s: %u\n", hash, name, hash(key, SIZE));
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
004014D6
00401533
0040157D

004014D6
00401533
0040157D


004014D6 RSHash      : 34
00401533 DEKHash     : 5
0040157D DJBHash     : 27

004014D6 RSHash      : 34
00401533 DEKHash     : 5
0040157D DJBHash     : 27
*/
