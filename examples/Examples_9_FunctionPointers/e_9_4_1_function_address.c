/****************************************************************************

   The Address of a Function
   Declare a Pointer to a Function
   Initialize a Pointer to a Function

****************************************************************************/
#include <stdio.h>
#include <string.h>

#define SIZE 103

int main( void )
{
    unsigned int RSHash (const char *key, int size);
    unsigned int DEKHash(const char *key, int size);
    unsigned int DJBHash(const char *key, int size);

    // define a pointer to a function
    unsigned int (*hash)(const char *, int);
    char key[] = "Advanced C";

    printf("Address of RSHash : %p\n", RSHash);
    printf("Address of DEKHash: %p\n", DEKHash);
    printf("Address of DEKHash: %p\n\n", DJBHash);

    hash = RSHash;
    printf("                 RSHash: %u\n", RSHash(key, SIZE));
    printf("Using pointer to RSHash: %u\n\n", hash(key, SIZE));

    hash = DEKHash;
    printf("                 DEKHash: %u\n", DEKHash(key, SIZE));
    printf("Using pointer to DEKHash: %u\n\n", hash(key, SIZE));

    hash = DJBHash;
    printf("                 DJBHash: %u\n", DJBHash(key, SIZE));
    printf("Using pointer to DJBHash: %u\n\n", hash(key, SIZE));

    return 0;
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
Address of RSHash : 0040147B
Address of DEKHash: 004014D8
Address of DEKHash: 00401522

                 RSHash: 41
Using pointer to RSHash: 41

                 DEKHash: 30
Using pointer to DEKHash: 30

                 DJBHash: 41
Using pointer to DJBHash: 41
*/
