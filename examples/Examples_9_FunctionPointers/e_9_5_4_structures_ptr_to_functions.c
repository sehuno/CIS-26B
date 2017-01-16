/****************************************************************************

   An array of HASH structures
            - one of the fields is a pointer to a hash function

****************************************************************************/
#include <stdio.h>
#include <string.h>

#define SIZE 103

typedef struct
{
    char *name;
    unsigned int (*hash)(const char *key, int size);
} HASH;

int main( void )
{
    unsigned int RSHash(const char *key, int size);
    unsigned int DEKHash(const char *key, int size);
    unsigned int DJBHash(const char *key, int size);

    void printHash( const char *name, unsigned int (*hash)(const char *key, int size) );


    HASH hashList[] = // a list of HASH structures: name and function
    {
        {"RSHash", RSHash},
        {"DEKHash", DEKHash},
        {"DJBHash", DJBHash},
        {NULL, NULL}
    };

    HASH *mover;
    int i, n = 3;

    // Use an INDEX to print the address of each function in the list
    for (i = 0; i < n; i++)
        printf("%10s: %p\n", hashList[i].name, hashList[i].hash);
    printf("\n");

    // Use a POINTER to print the address of each function in the list
    for (mover = hashList; mover->hash; mover++)
        printf("%10s: %p\n", mover->name, mover->hash);
    printf("\n");
    printf("\n");


    // Use an INDEX to call the printHash function
    for (i = 0; i < n; i++)
        printHash( hashList[i].name, hashList[i].hash );
    printf("\n");

    // Use a POINTER to call the printHash function
    for (mover = hashList; mover->hash; mover++)
        printHash( mover->name, mover->hash );
    printf("\n");

    return 0;
}
/**************************************************
   Print Hash
*/
void printHash(  const char *name, unsigned int (*hash)(const char *key, int size) )
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
    RSHash: 004014C5
   DEKHash: 00401522
   DJBHash: 0040156C

    RSHash: 004014C5
   DEKHash: 00401522
   DJBHash: 0040156C


004014C5 RSHash      : 34
00401522 DEKHash     : 5
0040156C DJBHash     : 27

004014C5 RSHash      : 34
00401522 DEKHash     : 5
0040156C DJBHash     : 27
*/
