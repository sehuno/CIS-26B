#include "tree.h"

void writeInputFile(FILE* file, FILE * outfile);		// Write properly formatted inputfile to outputfile	
void writeNode(WORDNODE *node, FILE *outfile);			// Prints the word and calls writeQueue for its queue of lineNums
void writeQueue(LINE *line, FILE* outfile);				// Prints queue of lineNums		
void writeTree(WORDNODE *rootptr, FILE* outfile);		// Calls writeNode function starting from left most node to right most
void writeToFile(FILE *inputFile, FILE *outfile, WORDNODE* ptr);	// Calls the above mentioned write functions along with creation time 
