#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "queue.h"

#define LINEMAX 500


/*
WORDNODE will contain
	- a char pointer which will be used to dynamically allocate a char array containing the word
	- a LINE pointer which will be used to dynamically allocate a LINE structure 
	- a pointer to the left WORDNODE with ascii value of word smaller than that of its own
	- a pointer to the left WORDNODE with ascii value of word greater than that of its own
*/
typedef struct wordnode {		
	char *word;
	LINE *line;
	struct wordnode *left;
	struct wordnode *right;
} WORDNODE;


// TREE will contain a pointer to a WORDNODE which is a the root node of the tree
typedef struct tree {
	WORDNODE *root;
} TREE;

/*
STATE enum will be used for keeping track of processing state
	- BLANK means no token yet found and will skip chars that are unneeded
	- IN_TOKEN means we are in a token and will have to keep track of such token until it ends
	- IN_LIMBO means we are between double or single quotes, chars within it must not be processed
	- SHORT_COMMENT means that for the rest of the line should not be processed
	- LONG_COMMENT is similar to IN_LIMBO and will skip chars until the end of the long comment
*/
typedef enum states { 
  BLANK,
  IN_TOKEN,
  IN_LIMBO,
  SHORT_COMMENT,
  LONG_COMMENT
} STATE; 

TREE* generateTreeFromFile(FILE* fp);												// generates a binary tree from file 
void insertToTree(WORDNODE **rootptr, char **word, int wordLength, int lineNum);	// insert to tree 
WORDNODE **findElement(char **word, int wordLength, WORDNODE **rootptr);			// will return a two level pointer to a WORDNODE given word info and tree pointer
WORDNODE *newWordNode(char **word, int wordLength, int lineNum) ;					// create new word node from word info and linenum
void freeTree(WORDNODE* ptr);														// frees all dynamically allocated memory in tree