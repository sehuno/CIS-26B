/*********************************************************************************
** CIS 26B                                                      Winter, 2016
** Advanced C
******************
**
** Homework 2:
**      A Doubly Linked List of Rings
**
**********************************************************************************

   Create and process a doubly linked list of rings containing parks and computers 
    and allow the user to search for park and computer combinations.
    
**********************************************************
**
**  Written By:  Sehun Oh         // <-- write your name here
**
**  Date: 1/27/2016                 // <-- write the date here
**  IDE (compiler): gcc  
**  Operating System: Mac OS X El Capitan=
***************************************************************************/

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

// Function prototypes
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
    displayParkNames(parkring);
    displayReverseAll(parkring);
    searchForPark(parkring);
    freeAll(parkring);
}

// The readInFromFile function will prompt the user for the input file path and
//  and will return a pointer to a PARKRING object which will be dynamically allocated and sorted during allocation.
PARKRING* readInFromFile()
{
    // // 1. Get file path, open file
    FILE* fData;
    char file[300];
    // char file[300] = "/Users/sehun/Documents/26b/hw2/input.txt";

    // // Prompt user for file path and get rid of new line char
    printf("Enter file path for input file: ");
    fgets(file, sizeof(file), stdin);
    *(file + strlen(file) - 1) = '\0';

    // // Open file with filepath
    if((fData = fopen(file,"r")) == NULL)
    {
        printf("Error opening file at location %s!", file);
        exit(101);
    }

    // Create parkring
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
                // keep an alternating count between 0 and 1
                if(count == 0)
                {
                    // 0 represents computer name
                    strncpy(c_name, token, sizeof(c_name));
                    count++;
                }
                else
                {
                    // 1 represents the status of the computer
                    // remove tab
                    if(strlen(token) > 1)
                        *(token + strlen(token) - 1) = '\0';
                    // translate string to int
                    stat = atoi(token);
                    // insert computer
                    insertCompNode(&new_park.compring, c_name, stat);
                    // return count back to 0
                    count = 0;
                }
                token = strtok(NULL, " ");
            }

        } while(cLineEnded);
        // Insert park
        insertParkNode(newring, &new_park);
    }
    // Close file
    fclose(fData);
    // Return parkring
    return newring;
}

// The createParkring function returns a newly created pointer to a PARKRING object
PARKRING* createParkring()
{
    PARKRING *newring = (PARKRING *) malloc(sizeof(PARKRING));
    newring->first = NULL;
    newring->last = NULL;
    newring->numParks = 0;
    return newring;
}

// The insertCompNode function will take in a COMPRING pointer, a name and an int representing 
//  the computer status and will insert a new computer object into the COMPRING
void insertCompNode(COMPRING *compring, char* name, int s)
{
    COMPNODE* new_node = (COMPNODE*)malloc(sizeof(COMPNODE));
    strcpy(new_node->comp.compName, name);
    new_node->comp.status = s;

    // Check for if empty
    if(compring->first == NULL && compring->last == NULL)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        compring->first = new_node;
        compring->last = new_node;
    }
    // Checks if there is only one computer
    else if(compring->first == compring->last)
    {
        new_node->prev = compring->first;
        new_node->next = compring->last;
        compring->last = new_node;
        compring->first->prev = new_node;
        compring->first->next = new_node;
    }
    // for any other case
    else
    {
        new_node->prev = compring->last;
        new_node->next = compring->first;
        compring->first->prev = new_node;
        compring->last->next = new_node;
        compring->last = new_node;
    }
    (compring->numComps)++;
}

// The insertParkNode function will take in a PARKRING pointer and a PARK pointer and will insert the PARK in it's
//  alphabetically sorted order.
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

// The displayParkNames function will take a PARKRING pointer and traverse the PARKRING
//  which was sorted alphabetically by park names as the parks were inserted into the
//  parkring. 
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

// The displayReverseAll function will take in a PARKRING pointer and will traverse in reverse order
//  displaying the park name and the computer names and statuses. 
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

// The searchForPark will take in a PARKRING pointer and will prompt the user for the park name and computer name
//  that they wish to search for and performs input validation before passing to functions checkPark and checkComp which will validate
//  their existence.
void searchForPark(PARKRING *parkring)
{

    char park_input[31];
    char comp_input[21];
    char input[31];

    printf("\n=== Entering search mode for parks and computers ===\n*** Type 'quit' to exit program ***\n");
    while(1)
    {
        // Prompts user for the park name and performs input validation
        printf("\n    Park name?  ");
        fgets(input, sizeof(input), stdin);
        *(input + strlen(input) - 1) = '\0';
        // Conversion to lower case
        char *lowerinput = strToLower(input);
        // Checks whether string was 'quit'
        if(strcmp("quit", lowerinput) == 0)
        {
            free(lowerinput);
            printf("\n 	EXITING PROGRAM. GOODBYE\n");
            break;
        }
        else
            strcpy(park_input, lowerinput);
        free(lowerinput);

        // Prompts users for the computer name and performs input validation
        printf("Computer name?  ");
        fgets(input, sizeof(input), stdin);
        *(input + strlen(input) - 1) = '\0';
        // Conversion to lower case
        char *space = strchr(input, ' ');
        // Removes the later parts of the computer name only to take the first word
        if(space != NULL)
            *space = '\0';
        // Conversion to lower case
        char *lowerinput2 = strToLower(input);
        // Checks whther string was 'quit'
        if(strcmp("quit", lowerinput2) == 0)
        {
            free(lowerinput2);
            printf("\n 	EXITING PROGRAM. GOODBYE\n");
            break;
        }
        else
            strcpy(comp_input, lowerinput2);
        free(lowerinput2);

        // Checks validation for numberical characters within input
        if(containsDigit(park_input) || containsDigit(comp_input))
            printf("\n 	ERROR: INPUT CANNOT CONTAIN A DIGIT\n");
        else
            checkComputer(checkPark(park_input,parkring->first), comp_input);
    }
}

// The checkPark function will take in a char pointer for the park name and PARKNODE pointer
//  which will traverse through the parkring and check whether such park exists. If it exists
//  the function will return the PARKNODE pointer, if not, it will return null.
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

// The checkComputer will take in a PARKNODE pointer and a char pointer containing the computer name
//  It will then traverse the COMPRING object for the park node and will check whether the name exists.
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

// The strToLower function will take a in a char pointer and 
//  return a char pointer to the string converted to all lowercase characters
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

// The neighborInfo function will take in a COMPNODE pointer and will check its left and right COMPNODE objects
//  to check their statuses and will print the appropriate messages regarding status, distance, and whether or not 
//  such an up computer exists.
void neighborInfo(COMPNODE *node)
{
    // right and left are counters for keeping track of count for distance 
    int right = 1;
    int left = 1;
    // two pointers set to left and right of the given COMPNODE
    COMPNODE* ptr = node->next;
    COMPNODE* ptr2 = node->prev;

    // travere right
    while(ptr != node)
    {
        if(ptr->comp.status == 1)
            break;
        else {
            ptr = ptr->next;
            right++;
        }
    }
    // traverse left
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

    // Print appropriate messages when the traversal is done
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

// The containsDigit will take in a char pointer and return a bool 
//  on whether or not the string contains a digit.
bool containsDigit(char *s)
{
    char *ptr = malloc(sizeof(char) * 31);
    char *ptr2;
    strcpy(ptr, s);
    ptr2 = ptr;
    // While not the end of the string
    while(*ptr2 != '\0')
    {
        // if current character is a digit return true
        if(isdigit(*ptr2)) {
            free(ptr);
            return true;
        }
        ptr2++;
    }
    free(ptr);
    return false;
}

// The freeAll function will take in a PARKRING pointer and free all dynamically
//  allocated memory by traversing through each park and its COMPRING object and 
//  freeing all computers.
void freeAll(PARKRING* ring)
{
    PARKRING* ring_ptr = ring;
    if(ring->first == ring_ptr->last)
        free(ring_ptr->last);
    else
    {
        PARKNODE* ptr = ring_ptr->first;
        while(ptr != ring_ptr->last)
        {
            COMPNODE* cptr = ptr->park.compring.first;
            while(cptr != ptr->park.compring.last)
            {
                cptr = cptr->next;
                free(cptr->prev);
                cptr->prev = NULL;
            }
            free(ptr->park.compring.last);
            cptr = NULL;
            ptr = ptr->next;
            free(ptr->prev);
            ptr->prev = NULL;
        }
        free(ring_ptr->last);
        ptr = NULL;
    }
    free(ring);
    ring = NULL;
}


/* 
OUTPUT:

Enter file path for input file: /Users/sehun/Documents/26b/hw2/input.txt

Alphabetically sorted list of park names:
Big Basin
Big Sur
Death Valley
Devils Postpile
Joshua Tree
Kings Canyon
Lasen Volcanic
Pinnacles
Point Reyes
Redwood
Yosemite

Reverse alphabetically sorted list of parks and their information:

Park Name: Yosemite
   Computer:              caligula  Status: 1
   Computer:               theorem  Status: 1
   Computer:                  star  Status: 1
   Computer:              catalyst  Status: 0
   Computer:                 pixel  Status: 0
   Computer:               quantum  Status: 1
   Computer:                 spock  Status: 0
   Computer:                   son  Status: 0

Park Name: Redwood
   Computer:                 turbo  Status: 0
   Computer:               voyager  Status: 1
   Computer:                crypto  Status: 1
   Computer:                magnus  Status: 0
   Computer:                  nero  Status: 0
   Computer:               galileo  Status: 0
   Computer:               citadel  Status: 1
   Computer:                  odin  Status: 0
   Computer:                proton  Status: 0

Park Name: Point Reyes
   Computer:                 amber  Status: 0
   Computer:                  zion  Status: 0
   Computer:                 brice  Status: 0
   Computer:                 beron  Status: 0
   Computer:                cypher  Status: 0
   Computer:                 venus  Status: 1
   Computer:                saturn  Status: 0
   Computer:                  luna  Status: 0
   Computer:                merlin  Status: 0
   Computer:                  mars  Status: 0

Park Name: Pinnacles
   Computer:                 eniac  Status: 0
   Computer:                  khan  Status: 1
   Computer:                   hal  Status: 1
   Computer:                   box  Status: 0
   Computer:                 gizmo  Status: 1

Park Name: Lasen Volcanic
   Computer:                 zelda  Status: 1
   Computer:                  flux  Status: 1
   Computer:                 hydra  Status: 1
   Computer:                willow  Status: 1
   Computer:                 swift  Status: 1
   Computer:                  aeon  Status: 1
   Computer:               neptune  Status: 1

Park Name: Kings Canyon
   Computer:                animus  Status: 1
   Computer:                  xena  Status: 0
   Computer:              santiago  Status: 1
   Computer:                   hex  Status: 0
   Computer:               laplace  Status: 1
   Computer:                 mario  Status: 0

Park Name: Joshua Tree
   Computer:                 golem  Status: 0
   Computer:                  pyro  Status: 0
   Computer:                 unity  Status: 0
   Computer:                tardis  Status: 0
   Computer:                  hawk  Status: 0
   Computer:                 pluto  Status: 0

Park Name: Devils Postpile
   Computer:              minotaur  Status: 1
   Computer:                enigma  Status: 1
   Computer:                  ezra  Status: 0
   Computer:                  nero  Status: 0
   Computer:               reflect  Status: 1
   Computer:                canary  Status: 1
   Computer:                  thor  Status: 0
   Computer:                switch  Status: 0
   Computer:               mercury  Status: 1
   Computer:                  loki  Status: 1

Park Name: Death Valley
   Computer:                   neo  Status: 0
   Computer:                 thebe  Status: 0
   Computer:                 titus  Status: 0
   Computer:             telescope  Status: 1
   Computer:                mosaic  Status: 0
   Computer:             zabrinski  Status: 0
   Computer:                 dante  Status: 1
   Computer:                 chaos  Status: 0
   Computer:                   ego  Status: 0
   Computer:                vortex  Status: 0

Park Name: Big Sur
   Computer:                fusion  Status: 1
   Computer:                  puma  Status: 0
   Computer:                 tiger  Status: 0
   Computer:                  lion  Status: 1
   Computer:                 rogue  Status: 1
   Computer:                aurora  Status: 0
   Computer:                  link  Status: 0

Park Name: Big Basin
   Computer:                hamlet  Status: 0
   Computer:                 river  Status: 1
   Computer:                 moose  Status: 0
   Computer:                 blaze  Status: 0
   Computer:                 pluto  Status: 1
   Computer:                 felix  Status: 0
   Computer:               genesis  Status: 0
   Computer:              amethyst  Status: 1

=== Entering search mode for parks and computers ===
*** Type 'quit' to exit program ***

    Park name?  Lasen Volcanic
Computer name?  willow

    The nearest neighboring up computers are 'swift' and 'hydra'

    Park name?  Devils Postpile
Computer name?  mercury

    The nearest neighboring up computer is 'loki'

    Park name?  Redwood
Computer name?  citadel

    The nearest neighboring up computers are 'voyager' and 'crypto'

    Park name?  Death Valley
Computer name?  dante

    There is only one up neighbor computer 'telescope'

    Park name?  Point Reyes
Computer name?  venus

    There is no up neighbor computers

    Park name?  PInnacles
Computer name?  mouse

    Park name found; COMPUTER DOES NOT EXIST

    Park name?  Cupertino
Computer name?  amethyst

    PARK DOES NOT EXIST

    Park name?  lasen volcanic
Computer name?  Willow

    The nearest neighboring up computers are 'swift' and 'hydra'

    Park name?  BIG SUR
Computer name?  rogue 123 tiger

    The nearest neighboring up computer is 'lion'

    Park name?  BIG 123
Computer name?  rogue

    ERROR: INPUT CANNOT CONTAIN A DIGIT

    Park name?  BIG SUR
Computer name?  rogue007

    ERROR: INPUT CANNOT CONTAIN A DIGIT

    Park name?  quit

    EXITING PROGRAM. GOODBYE

*/
