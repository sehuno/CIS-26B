#include "write.h"

int main(int argc, char **argv) 
{
	FILE *inputFile, *outputFile;		// Two file pointers for input file and output file
 	TREE *tree;							// Tree pointer for tree of word nodes

	inputFile = fopen(argv[1], "r");	// Open inputfile using the first argument being the input file path 
	if(!inputFile)											// if error opening, print message and exit program.
		printf("Error opening file!!!\n"), exit(101); 

	tree = generateTreeFromFile(inputFile);				// generates tree of word nodes from the inputfile

	writeToFile(inputFile, outputFile, tree->root);		// writes the cross reference listing and timestamp to the output file 

	freeTree(tree->root); free(tree);					// free all dynamically allocated memory

	fclose(inputFile); fclose(outputFile);				// closes file pointers after use.

	return 0;
}