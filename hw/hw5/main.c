#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define LINEMAX 500

typedef struct queue_node {
	int num;
	struct queue_node *next;
} Q_NODE; 

typedef struct line {
	Q_NODE *first;
	Q_NODE *last;
} LINE;

typedef struct wordnode {
	char *word;
	LINE *line;
	struct wordnode *left;
	struct wordnode *right;
} WORDNODE;

typedef struct tree {
	WORDNODE *root;
} TREE;

typedef enum states { 
  BLANK,
  IN_TOKEN,
  IN_LIMBO,
  SHORT_COMMENT,
  LONG_COMMENT
} STATE; 


void writeInputFile(FILE* file, FILE * outfile);
void writeNode(WORDNODE *node, FILE *outfile);
void writeQueue(LINE *line, FILE* outfile);
void writeTree(WORDNODE *rootptr, FILE* outfile);
void writeToFile(FILE *inputFile, FILE *outfile, WORDNODE* ptr);

WORDNODE **findElement(char **word, int wordLength, WORDNODE **rootptr);
WORDNODE *newWordNode(char **word, int wordLength, int lineNum) ;
void insertToTree(WORDNODE **rootptr, char **word, int wordLength, int lineNum);
LINE *newLineQueue();
void insertToQueue(LINE *lineptr, int lineNum);
void freeLine(LINE *lineptr);


void freeQueue(Q_NODE *ptr);

TREE* generateTreeFromFile(FILE* fp);


int main(int argc, char **argv) 
{
	FILE *inputFile, *outputFile;
	char line[LINEMAX];
 	TREE *tree;

	inputFile = fopen(argv[1], "r");
	if(!inputFile)
		printf("Error opening file!!!\n"), exit(101); 

	tree = generateTreeFromFile(inputFile);

	writeToFile(inputFile, outputFile, tree->root);

	fclose(inputFile); fclose(outputFile);

	return 0;
}

TREE* generateTreeFromFile(FILE* fp) 
{
	char line[LINEMAX];
	char word[500];	
	char *p, *token_start;
	char limbo_char;

	int tokenLength;
	int lineLength;
	int lineNum = 1;
	int count;

	STATE state = BLANK;

	TREE *tree = (TREE *) malloc(1 * sizeof(TREE));
	tree->root = NULL;

	while(fgets(line, LINEMAX, fp) != NULL)
	{
		p = line;
		count = 1;
		lineLength = strlen(line);
		// printf("\n%d ", lineNum);

		while(count < lineLength && state != SHORT_COMMENT)
		{
			switch(state) {
				case BLANK: 
					{
						if(isspace(*p)){
							p++; count++; break;
						}

						if(*p == '/' && *(p+1) == '/') {
							state = SHORT_COMMENT; break;
						}

						if(*p == '/' && *(p+1) == '*'){
							state = LONG_COMMENT; p += 2; count += 2; break;
						}

						if(*p == '\'' || *p == '\"') {
							limbo_char = *p; p++; count ++; state = IN_LIMBO; break;
						}

						if(!isalpha(*p) || *p == ';'){
							p++; count++; break;
						}

						if(isalpha(*p)){
							token_start = p; tokenLength = 1; p++; count++; state = IN_TOKEN; break; 
						}
					}
				
				case IN_TOKEN:
					{
						if(*p == '_' || isalpha(*p) || isdigit(*p)) {
							tokenLength++; p++; count++; break;
						}
						else{
							if(strncmp("include", token_start, 7) == 0) {
								// strncpy(word, token_start, tokenLength);
								// printf("%.*s", tokenLength, token_start); 
								insertToTree(&(tree->root), &token_start, tokenLength, lineNum);
								state = SHORT_COMMENT; break;
							} 
							else {
								// strncpy(word, token_start, tokenLength);
								insertToTree(&(tree->root), &token_start, tokenLength, lineNum);
								// printf("%.*s", tokenLength, token_start);
								state = BLANK; p++; count++; break;
							}
						}
					}

				case IN_LIMBO:
					{
						if(*p == '\\') {
							p +=2; count +=2; break;
						}

						if(*p == limbo_char) {
							state = BLANK; p++; count++; break;
						}
					}

				case LONG_COMMENT:
					{
						if(*p == '*' && *p == '/') {
							state = BLANK; p += 2; count += 2; break;
						}
						else {
							p++; count++; break;
						}
					}

				default:
					break;
			}
		}

		if(state == SHORT_COMMENT)
			state = BLANK;

		if (state == IN_TOKEN) {
			// printf("%.*s", tokenLength, token_start);
			insertToTree(&(tree->root), &token_start, tokenLength, lineNum);
			state = BLANK;
		}
		lineNum++;
	}
	return tree;
}

// TWO-LEVEL PTR
WORDNODE **findElement(char **word, int wordLength, WORDNODE **rootptr)
{
	WORDNODE *ptr = *rootptr;
	while(ptr != NULL)		// while node not null
	{
		if(strncmp(*word, ptr->word, strlen(ptr->word)) < 0) {	// traverse left
			rootptr = &(ptr->left);			// rootptr points to the address of node's left subtree root node
			ptr = ptr->left;				// ptr now points to node's left subtree root node
		} 
		else if(strncmp(*word, ptr->word, strlen(ptr->word)) > 0)  {		// traverse right
			rootptr = &(ptr->right);		// rootptr points to the address of node's right subtree root node
			ptr = ptr->right;				// ptr now points to node's right subtree root node
		}
		else 
			return rootptr;					// rootptr returned here means node found with word
	}
	return rootptr;							// rootptr returned here means node was not found and will be null
}


// LINE FUNCTIONS
LINE *newLineQueue() 
{
	LINE *line = (LINE *) malloc(1 * sizeof(LINE));
	line->first = line->last = NULL;
	return line;
}

void insertToQueue(LINE *lineptr, int lineNum) 
{	
	if(lineptr->first == NULL) {
		Q_NODE *newNode = (Q_NODE *) malloc(1 * sizeof(Q_NODE));	// create new Q_NODE
		newNode->num = lineNum;										// newNode's num is the lineNum passed
		newNode->next = NULL;										// newNode's next is NULL
 		lineptr->first = lineptr->last = newNode;					// if none in queue
 	} 
 	else {
 		if(lineptr->last->num == lineNum)
 			return;
 		else {
 			Q_NODE *newNode = (Q_NODE *) malloc(1 * sizeof(Q_NODE));	// create new Q_NODE
			newNode->num = lineNum;										// newNode's num is the lineNum passed
			newNode->next = NULL;										// newNode's next is NULL
 			lineptr->last->next = newNode;						// Add to the last queue node
			lineptr->last = newNode;							// Make new node the last queue node
 		}
 	}	
}	

void freeLine(LINE *lineptr)
{
	freeQueue(lineptr->first);
	free(lineptr);
}

void freeQueue(Q_NODE *ptr)
{
	if(!ptr)
		return;
	freeQueue(ptr->next);
	free(ptr);
}

void writeQueue(LINE *line, FILE* outfile)
{
	int i = 0;
	Q_NODE *ptr = line->first;
	while(ptr != NULL) {
		if(i == 9) {
			fprintf(outfile, "\n%23s", "");
			i = -1;
		}
		if(ptr->num > 9)
			fprintf(outfile, "%-5d", ptr->num); 
		else
			fprintf(outfile, " %-4d", ptr->num);
		ptr = ptr->next;
		i++;
	}
	fprintf(outfile, "\n");
}

// WORDNODE functions
WORDNODE *newWordNode(char **word, int wordLength, int lineNum) 
{
	int i; 
	WORDNODE *newNode = (WORDNODE *) malloc(sizeof(WORDNODE));
	newNode->word = (char *) malloc(sizeof(char) * (wordLength+1));

	for(i = 0; i < wordLength; i++)
		(newNode->word)[i] = *(*word+i);
	(newNode->word)[wordLength] = '\0';

	newNode->line = newLineQueue();

	// printf("%s newwordnode inserts %d\n", newNode->word, lineNum);
	insertToQueue(newNode->line, lineNum);

	newNode->left = NULL; newNode->right = NULL;
	return newNode;
}

void writeNode(WORDNODE *node, FILE *outfile)
{
	fprintf(outfile, "%-23s", node->word);		// print the word
	writeQueue(node->line, outfile);
}


void insertToTree(WORDNODE **rootptr, char **word, int wordLength, int lineNum)
{
	WORDNODE **ptr;
	if(*rootptr == NULL) 
		*rootptr = newWordNode(word, wordLength, lineNum);
	else {
		ptr = findElement(word, wordLength, rootptr);
		if(*ptr == NULL) 
			*ptr = newWordNode(word, wordLength, lineNum);
		else 
			insertToQueue((*ptr)->line, lineNum);
	}
}

void writeToFile(FILE* inputFile, FILE *outfile, WORDNODE* ptr)
{
	time_t ltime; 			/* calendar time */
    ltime = time(NULL); 	/* get current cal time */

	outfile = fopen("output.txt", "w");
	if(outfile == NULL) {
		printf("error opening output file!!!"); exit(102);
	}

	fprintf(outfile, "/************************  Cross Reference Listing  ************************/\n\n");
	fprintf(outfile, "Cross reference listing made at:  %s\n\n", asctime(localtime(&ltime)));
	writeTree(ptr, outfile);
	fprintf(outfile, "\n");
	writeInputFile(inputFile, outfile);

}

void writeTree(WORDNODE *rootptr, FILE* outfile)
{
	if(rootptr == NULL)
		return;
	writeTree(rootptr->left, outfile);
	writeNode(rootptr, outfile);
	writeTree(rootptr->right, outfile);
}

void writeInputFile(FILE* file, FILE* outfile) 
{
	rewind(file);
	int lineNum = 1;
	char line[500];
	while(fgets(line, 500, file) != NULL) 
		fprintf(outfile, "%-3d    : %s", lineNum++, line);
	fprintf(outfile, "\n");
}	