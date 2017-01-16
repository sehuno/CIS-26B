#include "tree.h"

// generates a binary search tree from file 
TREE* generateTreeFromFile(FILE* fp) 
{
	char line[LINEMAX];		// char array to hold line read in from file
	char *p, *token_start;	// two pointers to traverse char array character by character
	char limbo_char;		// will hold single quote or double quote to properly skip tokens within quotes and know when to end

	int tokenLength;		// incremented to keep track of token length
	int lineLength;			// length of line to know when end of line is reached (end of line is not ALWAYS \n)
	int lineNum = 1;		// incremented to keep track of line number
	int count;				// incremented to keep track of how far traversed in line

	STATE state = BLANK;	// processing state

	TREE *tree = (TREE *) malloc(1 * sizeof(TREE));		// dynamically allocate tree pointer
	tree->root = NULL;									// root set to null

	while(fgets(line, LINEMAX, fp) != NULL)				// while line was read in from file
	{
		p = line;						// p pointer starts at beginning of line
		count = 1;						// count shows position in comparison to lineLength
		lineLength = strlen(line);		// line length

		while(count < lineLength && state != SHORT_COMMENT)		// only enter loop if p not end of line and line is not a comment
		{
			switch(state) {
				case BLANK: 
					{
						if(isspace(*p)){				// skip spaces
							p++; count++; break;
						}

						if(*p == '/' && *(p+1) == '/') {	// if two consecutive forward slashes, comment line state started
							state = SHORT_COMMENT; break;	
						}

						if(*p == '/' && *(p+1) == '*'){		// if forward slash and star found, long comment state started
							state = LONG_COMMENT; p += 2; count += 2; break;
						}

						if(*p == '\'' || *p == '\"') {		// if quotes found, enter limbo where chars are not processed within quotes
							limbo_char = *p; p++; count ++; state = IN_LIMBO; break;
						}

						if(!isalpha(*p) || *p == ';'){		// if char is not any of above and is not an alpha character, skip char
							p++; count++; break;
						}

						if(isalpha(*p)){	// if char is alpha, token_start pointer points to current char, start incrementing token length from 1, enter token state
							token_start = p; tokenLength = 1; p++; count++; state = IN_TOKEN; break; 
						}
					}
				
				case IN_TOKEN:
					{
						if(*p == '_' || isalpha(*p) || isdigit(*p)) {	// increment token if valid token char
							tokenLength++; p++; count++; break;
						}
						else{	
							if(strncmp("include", token_start, 7) == 0) {	// if line included the word include, skip the rest of line
								insertToTree(&(tree->root), &token_start, tokenLength, lineNum);	// insert token to tree
								state = SHORT_COMMENT; break;
							} 
							else {	// otherwise, call insertToTree with token information, end token 
								insertToTree(&(tree->root), &token_start, tokenLength, lineNum);
								state = BLANK; p++; count++; break;
							}
						}
					}

				case IN_LIMBO:
					{
						if(*p == '\\') {				// skip reading backslashes
							p +=2; count +=2; break;	// *note*: when looking for single or double quote characters, the back slash is used 
						}

						if(*p == limbo_char) {			// if same limbo char found, single or double quote, end limbo
							state = BLANK; p++; count++; break;
						}
					}

				case LONG_COMMENT:
					{
						if(*p == '*' && *p == '/') {	// long comment end found, exit long comment state
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

		if(state == SHORT_COMMENT)		// short comment state will skip line, must reset for new line
			state = BLANK;

		if (state == IN_TOKEN) {		// if still in token at end of line, end the token and add to line
			insertToTree(&(tree->root), &token_start, tokenLength, lineNum);
			state = BLANK;
		}
		lineNum++;
	}
	return tree;
}

// will return a two level pointer to a WORDNODE given word info and tree pointer
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

// creates new WORDNODE from word info and linenum
WORDNODE *newWordNode(char **word, int wordLength, int lineNum) 
{
	int i; 
	WORDNODE *newNode = (WORDNODE *) malloc(sizeof(WORDNODE));			// allocate new WORDNODE
	newNode->word = (char *) malloc(sizeof(char) * (wordLength+1));		// allocate char array with size as wordLength + 1

	for(i = 0; i < wordLength; i++)				// for 0 .. wordLength, copy each char into char array
		(newNode->word)[i] = *(*word+i);
	(newNode->word)[wordLength] = '\0';

	newNode->line = newLineQueue();				// for wordnode, create new line queue
	insertToQueue(newNode->line, lineNum);		// insert to the line queue the line number

	newNode->left = NULL; newNode->right = NULL;	// set node's left and right values to null
	return newNode;								// return the node
}

// insert to tree 
void insertToTree(WORDNODE **rootptr, char **word, int wordLength, int lineNum)
{
	WORDNODE **ptr;
	if(*rootptr == NULL) 										// if nothing in tree enter new node
		*rootptr = newWordNode(word, wordLength, lineNum);
	else {														
		ptr = findElement(word, wordLength, rootptr);			// findelement will return a double pointer
		if(*ptr == NULL) 
			*ptr = newWordNode(word, wordLength, lineNum);		// the pointer will be null if word was not found so create new wordnode
		else 
			insertToQueue((*ptr)->line, lineNum);				// if not null, wordnode with word exists so just add to queue
	}
}

// frees all dynamically allocated memory in tree
void freeTree(WORDNODE *ptr)
{
	if(ptr == NULL)				// if node null, return
		return;
	freeTree(ptr->left);		// free left subtree
	freeTree(ptr->right);		// free right subtree
	freeLine(ptr->line);		// free node's queue
	free(ptr->word);			// free node's char array
	free(ptr);					// free current node
}
