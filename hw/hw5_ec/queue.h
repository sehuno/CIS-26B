#include <stdlib.h>

/*
Q_NODE will contain
	- a number for the line number
	- a pointer to the next Q_NODE
*/
typedef struct queue_node {
	int num;
	struct queue_node *next;
} Q_NODE; 


/*
LINE will contain
	- a pointer to the first Q_NODE
	- a pointer to the last Q_NODE for quick insertion to queue instead of 
		traversing the queue every time for an insert
*/
typedef struct line {
	Q_NODE *first;
	Q_NODE *last;
} LINE;

LINE *newLineQueue();								// returns a pointer to a new line queue
void insertToQueue(LINE *lineptr, int lineNum);		// inserts to a line queue
void freeLine(LINE *lineptr);						// frees all dynamically allocated queue 
void freeQueue(Q_NODE *ptr);						// frees all dynamically allocated queue nodes starting from first 		
