#include "queue.h"

// returns a pointer to a new line queue
LINE *newLineQueue() 
{
	LINE *line = (LINE *) malloc(1 * sizeof(LINE));		// dynamically allocate a new queue
	line->first = line->last = NULL;					// queue first and last are set to null
	return line;										// return pointer to line
}	

// inserts to a line queue
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

// frees all dynamically allocated queue
void freeLine(LINE *lineptr)
{
	freeQueue(lineptr->first);				// free the queue starting from the first queue node
	free(lineptr);							// free dynamically allocated line pointer
}

// frees all dynamically allocated queue nodes starting from first 		
void freeQueue(Q_NODE *ptr)
{	
	if(!ptr)					// if queue node is null, do nothing and return
		return;
	freeQueue(ptr->next);		// free the next pointer
	free(ptr);					// free current pointer
}	
