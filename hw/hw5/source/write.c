#include "write.h"
#include <time.h>

// Write properly formatted inputfile to outputfile	
void writeInputFile(FILE* file, FILE* outfile) 
{
	rewind(file);			// rewinds input file pointer to beginning of file
	int lineNum = 1;
	char line[LINEMAX];		// Reads in line from input file
	while(fgets(line, LINEMAX, file) != NULL) 					
		fprintf(outfile, "%-3d    : %s", lineNum++, line);		// prints to output file with left formatting
	fprintf(outfile, "\n");
}	

// Prints the word and calls writeQueue for its queue of lineNums
void writeNode(WORDNODE *node, FILE *outfile)
{
	fprintf(outfile, "%-23s", node->word);		// prints to file the node's word 
	writeQueue(node->line, outfile);			// prints to file the node's lineNum queue
}

// Prints queue of lineNums
void writeQueue(LINE *line, FILE* outfile)
{
	int i = 0;
	Q_NODE *ptr = line->first;			// start from first queue node
	while(ptr != NULL) {				// write until null is reached
		if(i == 9) {							// every 9 numbers, start a new line for lineNums
			fprintf(outfile, "\n%23s", "");		
			i = -1;
		}
		if(ptr->num > 9)							// if number is 2 digits, properly write format to file
			fprintf(outfile, "%-5d", ptr->num); 
		else
			fprintf(outfile, " %-4d", ptr->num);	// if number is 1 digits, properly write format to file
		ptr = ptr->next;
		i++;
	}
	fprintf(outfile, "\n");							
}

// Calls writeNode function starting from left most node to right most
void writeTree(WORDNODE *rootptr, FILE* outfile)
{			
	if(rootptr == NULL)						// if null, don't do anything
		return;
	writeTree(rootptr->left, outfile);		// write the left subtree
	writeNode(rootptr, outfile);			// write current node
	writeTree(rootptr->right, outfile);		// write right subtree
}

// Calls the above mentioned write functions along with creation time 
void writeToFile(FILE* inputFile, FILE *outfile, WORDNODE* ptr)
{
	time_t ltime; 			/* calendar time */
    ltime = time(NULL); 	/* get current cal time */

	outfile = fopen("output.txt", "w");							// open outputfile to write
	if(outfile == NULL) {										// if not opened print to stdout error message and end prog
		printf("error opening output file!!!"); exit(102);
	}

	fprintf(outfile, "/************************  Cross Reference Listing  ************************/\n\n");		// top line format
	fprintf(outfile, "Cross reference listing made at:  %s\n\n", asctime(localtime(&ltime)));					// creation time 
	writeTree(ptr, outfile);					// write the tree
	fprintf(outfile, "\n");						
	writeInputFile(inputFile, outfile);			// write the input file in proper format

}

