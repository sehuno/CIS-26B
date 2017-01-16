#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum { false, true } bool;
typedef struct compnode COMPNODE;
typedef struct parknode PARKNODE;
typedef struct comp {
    char compName[21];
    int status;
} COMP;

struct compnode {
    COMP comp;
    COMPNODE *prev;
    COMPNODE *next;
};

typedef struct compring {
    COMPNODE *first;
    COMPNODE *last;
    int numComps;
} COMPRING;

typedef struct park {
    char parkName[31];
    COMPRING compring;
} PARK;

struct parknode {
    PARK park;
    PARKNODE *prev;
    PARKNODE *next;
};

typedef struct parkring {
    PARKNODE *first;
    PARKNODE *last;
    int numParks;
} PARKRING;

void displayParkNames(PARKRING *parkring);
void displayReverseAll(PARKRING *parkring);
PARKRING* readInFromFile();
PARKRING* createParkring();
char *strToLower(char *s);
void neighborInfo(COMPNODE *node);
bool containsDigit(char *s);
PARKNODE* checkPark(char *input, PARKNODE *first);
void checkComputer(PARKNODE* park_node, char *comp);
void searchForPark(PARKRING *parkring) ;
void insertCompNode(COMPRING *compring, char* name, int s);
void insertParkNode(PARKRING *ring, PARK* park);
void freeAll(PARKRING* ring);

int main ()
{
    PARKRING *parkring = readInFromFile();
    // PARKRING *parkring = createParkring();
    // PARK park;
    // strcpy(park.parkName,"hello");
    // insertCompNode(&(park.compring), "zelda", 1);
    // insertCompNode(&(park.compring), "abc", 2);
    // insertCompNode(&(park.compring), "zeldaasdf", 3);
    // insertParkNode(parkring, &park);

    // PARK park2;
    // strcpy(park2.parkName,"bye");
    // insertCompNode(&(park2.compring), "zelda", 1);
    // insertCompNode(&(park2.compring), "abc", 2);
    // insertCompNode(&(park2.compring), "zeldaasdf", 3);
    // insertParkNode(parkring, &park2);

//    freeAll(parkring);

    displayParkNames(parkring);
    displayReverseAll(parkring);
    searchForPark(parkring);
    freeAll(parkring);
}

PARKRING* readInFromFile()
{
    // // 1. Get file path, open file
    FILE* fData;
    // char file[300];
    char file[300] = "/Users/sehun/Documents/26b/hw2/input.txt";

    // // Prompt user for file path and get rid of new line char
    // printf("Enter file path for input file: ");
    // fgets(file, sizeof(file), stdin);
    // *(file + strlen(file) - 1) = '\0';

    // // Open file with filepath
    if((fData = fopen(file,"r")) == NULL)
    {
        printf("Error opening file at location %s!", file);
        exit(101);
    }

    PARKRING* newring = createParkring();

    // While not end of file
    char line[300];
    while(!feof(fData))
    {
        // 1. read a line for park name, and create park
        fgets(line, sizeof(line),fData);
        *(line + strlen(line) - 1) = '\0';

        PARK new_park;
        strcpy(new_park.parkName, line);

        // Initialize park's compring
        new_park.compring.first = NULL;
        new_park.compring.last = NULL;
        new_park.compring.numComps = 0;

        // 2. Create computers for each park
        char c_name[21];
        int stat;
        int count = 0;
        bool cLineEnded;

        do
        {
            // Get computers line and remove new line
            fgets(line, sizeof(line),fData);
            if(*(line + strlen(line) - 1) == '\n')
                *(line + strlen(line) - 1) = '\0';
            // See if the computer line has ended, looking for '#'
            cLineEnded = (strrchr(line,'#') == NULL);

            // Tokenize the line
            char *token;
            // Get first token
            token = strtok(line, " ");

            // walk through other tokens
            while( token != NULL )
            {
                if(count == 0)
                {
                    strncpy(c_name, token, sizeof(c_name));
                    count++;
                }
                else
                {
                    if(strlen(token) > 1)
                        *(token + strlen(token) - 1) = '\0';
                    stat = atoi(token);
                    insertCompNode(&new_park.compring, c_name, stat);
                    // printf("%s %d\n", c_name, stat);
                    count = 0;
                }
                token = strtok(NULL, " ");
            }

        } while(cLineEnded);
        insertParkNode(newring, &new_park);
    }
    fclose(fData);
    return newring;
}

PARKRING* createParkring()
{
    PARKRING *newring = (PARKRING *) malloc(sizeof(PARKRING));
    newring->first = NULL;
    newring->last = NULL;
    newring->numParks = 0;
    return newring;
}

void insertCompNode(COMPRING *compring, char* name, int s)
{
    COMPNODE* new_node = (COMPNODE*)malloc(sizeof(COMPNODE));
    strcpy(new_node->comp.compName, name);
    new_node->comp.status = s;

// 	// Check for if new node is first
    if(compring->first == NULL && compring->last == NULL)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        compring->first = new_node;
        compring->last = new_node;
    }
    else if(compring->first == compring->last)
    {
        new_node->prev = compring->first;
        new_node->next = compring->last;
        compring->last = new_node;
        compring->first->prev = new_node;
        compring->first->next = new_node;
    }
    else
    {
        new_node->prev = compring->last;
        new_node->next = compring->first;
        compring->first->prev = new_node;
        (compring->last)->next = new_node;
        compring->last = new_node;
    }
    (compring->numComps)++;
}

void insertParkNode(PARKRING *ring, PARK* park)
{
    PARKNODE* new_node = (PARKNODE *)malloc(sizeof(PARKNODE));
    new_node->park = *park;
    if(ring->first == NULL &&  ring->last == NULL)
    {
        ring->first = new_node;
        ring->last = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    else
    {
        PARKNODE* ptr = ring->first;
        if(ptr->next == NULL && ptr->prev == NULL)
        {
            new_node->next = ptr;
            new_node->prev = ptr;
            ptr->prev = new_node;
            ptr->next = new_node;
            if(strcmp(ptr->park.parkName, park->parkName) > 0)
                ring->first = new_node;
            else
                ring->last = new_node;
        }
        else
        {
            if(strcmp(ptr->park.parkName, park->parkName) > 0)
            {
                new_node->next = ptr;
                new_node->prev = ptr->prev;
                ptr->prev = new_node;
                ring->first = new_node;
            }
            else
            {
                while(strcmp(ptr->park.parkName, park->parkName) < 0 && ptr != ring->last)
                    ptr = ptr->next;

                if(ptr == ring->last)
                {
                    ptr->next = new_node;
                    new_node->next = ring->first;
                    new_node->prev = ptr;
                    ring->first->prev = new_node;
                    ring->last = new_node;
                }
                else
                {
                    new_node->next = ptr;
                    new_node->prev = ptr->prev;
                    ptr->prev->next = new_node;
                    ptr->prev = new_node;
                }
            }
        }
    }

    (ring->numParks)++;
}

void displayParkNames(PARKRING *parkring)
{
    printf("\nAlphabetically sorted list of park names: \n");
    if(parkring == NULL)
    {
        printf("WARNING: No parks read in.\n");
    }
    else
    {
        PARKNODE *ptr = parkring->first;
        do
        {
            printf("%s\n", ptr->park.parkName);
            ptr = ptr->next;
        } while( ptr != parkring->first);
    }
}

void displayReverseAll(PARKRING *parkring)
{
    printf("\nReverse alphabetically sorted list of parks and their information:\n");
    if(parkring == NULL)
    {
        printf("WARNING: No parks read in.\n");
    }
    else
    {
        PARKNODE *ptr = parkring->last;
        do
        {
            printf("\nPark Name: %s\n", ptr->park.parkName);
            COMPNODE *cptr = ptr->park.compring.first;
            do
            {
                printf("   Computer: %21s 	Status: %d\n", cptr->comp.compName, cptr->comp.status);
                cptr = cptr->next;
            } while (cptr != ptr->park.compring.first);

            ptr = ptr->prev;
        } while( ptr != parkring->last);
    }
}

void searchForPark(PARKRING *parkring)
{

    char park_input[31];
    char comp_input[21];
    char input[31];

    printf("\n=== Entering search mode for parks and computers ===\n*** Type 'quit' to exit program ***\n");
    while(1)
    {

        printf("\n    Park name?  ");
        fgets(input, sizeof(input), stdin);
        *(input + strlen(input) - 1) = '\0';
        char *lowerinput = strToLower(input);
        if(strcmp("quit", lowerinput) == 0)
        {
            free(lowerinput);
            printf("\n 	EXITING PROGRAM. GOODBYE\n");
            break;
        }
        else
            strcpy(park_input, lowerinput);
        free(lowerinput);

        printf("Computer name?  ");
        fgets(input, sizeof(input), stdin);
        *(input + strlen(input) - 1) = '\0';
        char *space = strchr(input, ' ');
        if(space != NULL)
            *space = '\0';
        char *lowerinput2 = strToLower(input);
        if(strcmp("quit", lowerinput2) == 0)
        {
            free(lowerinput2);
            printf("\n 	EXITING PROGRAM. GOODBYE\n");
            break;
        }
        else
            strcpy(comp_input, lowerinput2);
        free(lowerinput2);

        if(containsDigit(park_input) || containsDigit(comp_input))
            printf("\n 	ERROR: INPUT CANNOT CONTAIN A DIGIT\n");
        else
            checkComputer(checkPark(park_input,parkring->first), comp_input);
    }
}

// will return null if park does not exist
// will return parknode if park exists
PARKNODE* checkPark(char *input, PARKNODE *first)
{
    PARKNODE *ptr = first;
    if(ptr == NULL)
        return NULL;
    else
    {
        do
        {
            char *ptr1 = strToLower(ptr->park.parkName);
            char *ptr2 = strToLower(input);

            if(strcmp(ptr1, ptr2) == 0)
            {
                free(ptr1);
                free(ptr2);
                return ptr;
            }
            else
            {
                free(ptr1);
                free(ptr2);
                ptr = ptr->next;
            }
        } while(ptr != first && ptr != NULL);

        return NULL;
    }
}

void checkComputer(PARKNODE* park_node, char *comp)
{
    if(park_node == NULL)
    {
        printf("\n 	PARK DOES NOT EXIST\n");
    }
    else
    {
        COMPNODE *ptr = park_node->park.compring.first;
        if(ptr == NULL)
            printf("\n 	Park name found; COMPUTER DOES NOT EXIST\n");
        else
        {
            do
            {
                char *ptr1 = strToLower(ptr->comp.compName);
                char *ptr2 = strToLower(comp);
                if(strcmp(ptr1, ptr2) == 0) {
                    neighborInfo(ptr);
                    // printf("%s exists\n", ptr->comp.compName);
                    free(ptr1);
                    free(ptr2);
                    return;
                }
                else{
                    ptr = ptr->next;
                    free(ptr1);
                    free(ptr2);
                }
            } while(ptr != park_node->park.compring.first && ptr != NULL);
            printf("\n 	Park name found; COMPUTER DOES NOT EXIST\n");
        }
    }
    return;
}

char *strToLower(char *s)
{
    char *ptr = malloc(sizeof(char) * 30);
    char *ptr2;
    strcpy(ptr, s);
    ptr2 = ptr;
    while(*ptr2 != '\0')
    {
        *ptr2 = tolower(*ptr2);
        ptr2++;
    }
    return ptr;
}

void neighborInfo(COMPNODE *node)
{
    COMPNODE* ptr = node->next;
    int right = 1;
    COMPNODE* ptr2 = node->prev;
    int left = 1;
    while(ptr != node)
    {
        if(ptr->comp.status == 1)
            break;
        else {
            ptr = ptr->next;
            right++;
        }
    }
    while(ptr2 != node)
    {
        if(ptr2->comp.status == 1)
            break;
        else
        {
            ptr2 = ptr2->prev;
            left++;
        }
    }

    if(ptr == ptr2 && ptr != node)
        printf("\n 	There is only one up neighbor computer '%s'\n",ptr->comp.compName);
    else if(ptr == node && ptr2 == node)
        printf("\n 	There is no up neighbor computers\n");
    else
    {
        if(right == left)
            printf("\n 	The nearest neighboring up computers are '%s' and '%s'\n", ptr->comp.compName, ptr2->comp.compName);
        else if(right < left)
            printf("\n 	The nearest neighboring up computer is '%s'\n",ptr->comp.compName);
        else
            printf("\n 	The nearest neighboring up computer is '%s'\n", ptr2->comp.compName );
    }
}

bool containsDigit(char *s)
{
    char *ptr = malloc(sizeof(char) * 31);
    char *ptr2;
    strcpy(ptr, s);
    ptr2 = ptr;
    while(*ptr2 != '\0')
    {
        if(isdigit(*ptr2)) {
            free(ptr);
            return true;
        }
        ptr2++;
    }
    free(ptr);
    return false;
}

void freeAll(PARKRING* ring)
{
    PARKRING* ring_ptr = ring;
    if(ring->first == ring_ptr->last)
        free(ring_ptr->last);
    free(ring);

    // PARKNODE *ptr = ring->first;
    // while(ptr != ring->last)
    // {
    // 	PARKNODE *temp = ptr;
    // 	if(ptr->next != NULL)
    // 		temp = ptr->next;
    // 	COMPNODE *cptr = ptr->park.compring.first;
    // 	while(cptr != ptr->park.compring.last)
    // 	{
    // 		COMPNODE *ctemp = cptr;
    // 		if(cptr->next != NULL)
    // 			ctemp = cptr->next;
    // 		free(cptr);
    // 		cptr = ctemp;
    // 	}
    // 	// free(ptr->park.compring->first);
    // 	// free(ptr->park.compring->last);
    // 	free(ptr);
    // 	ptr = temp;
    // }
    // // free(ring->first);
    // // free(ring->last);
    // free(ring);
}
