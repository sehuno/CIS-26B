/*********************************************************************************
** CIS 26B                                                      Winter, 2016
** Advanced C
******************
**
** Homework 4:
**      Bit Manipulation
**
**********************************************************************************
    
    
**********************************************************
**
**  Written By:  Sehun Oh         // <-- write your name here
**
**  Date: 2/24/2016                 // <-- write the date here
**  IDE (compiler): gcc  
**  Operating System: Mac OS X El Capitan=
***************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINEMAX 100
#define NUMBITS 16

// macro return values
#define BADLINE -2
#define BLANK -1
#define ALLOFF 0
#define ALLON 1
#define LEFT_ON 2
#define CENTER_ON 3
#define RIGHT_ON 4
#define LEFT_OFF 5
#define CENTER_OFF 6
#define RIGHT_OFF 7
#define OVERLAY 8
#define QUIT 9

// Macro functions with arguments
#define TURN_ALL_OFF(config) (config = ALLOFF)
#define TURN_ALL_ON(config) (config = ~ALLOFF)
#define TURN_LEFT_ON(config) (config |= ((unsigned short) ~0 << 11))
#define TURN_LEFT_OFF(config) (config &= ~((unsigned short) 63488))
#define TURN_CENTER_ON(config) (config |= ((((unsigned short) ~0) >> 5) ^ (NUMBITS*2 - 1)))
#define TURN_CENTER_OFF(config) (config &= ~((unsigned short) (NUMBITS*4 - 1) << 5))
#define TURN_RIGHT_ON(config) (config |= (unsigned short) (NUMBITS*2 - 1))
#define TURN_RIGHT_OFF(config) (config = (config >> 5) << 5)

// use of boolean
typedef enum { false, true } bool;

// helper functions 
int menu();
void printbits(unsigned short wrd);
unsigned short bitOverlay(unsigned short config);
int testbit(unsigned short wrd, int bit_to_test);

int main() 
{
	int option;
	unsigned short config = (unsigned short) ~ALLOFF;
    unsigned short mask;

    // While the user has entered the choice to quit, loop the menu function
	while ((option = menu()) != QUIT)
    {
        // For the corresponding choices, perform the appropriate bit manipulation
        switch (option)
        {
            case ALLOFF: 
                TURN_ALL_OFF(config); break;
            case ALLON: 
                TURN_ALL_ON(config); break;
            case LEFT_ON: 
                TURN_LEFT_ON(config); break;
            case CENTER_ON: 
                TURN_CENTER_ON(config); break;
            case RIGHT_ON: 
                TURN_RIGHT_ON(config); break;
            case LEFT_OFF: 
                TURN_LEFT_OFF(config); break;
            case CENTER_OFF: 
                TURN_CENTER_OFF(config); break;
            case RIGHT_OFF: 
                TURN_RIGHT_OFF(config); break;
            // For the overlay choice, call the overlay function
            case OVERLAY: 
                config = bitOverlay(config);
                break;
            default:
                break;
        }
        printf("\nCurrent light configuration\n");
        printbits(config);
    }
}

int menu() 
{
    int choice;
    char input[50];
    char *token;

    // Print to screen the menu for light configuration options
    printf("\n=== Choose light configuration ===\n");
    printf("\n0) turn off all lights\n");
	printf("1) turn on all lights\n");
	printf("2) turn on left stage lights (lights 11-15)\n");
	printf("3) turn on center stage lights (lights 5-10)\n");
	printf("4) turn on right stage lights (lights 0-4)\n");
	printf("5) turn off left stage lights\n");
	printf("6) turn off center stage lights\n");
	printf("7) turn off right stage lights\n");
	printf("8) overlay on/off pattern onto light configuration \n");
	printf("9) quit the menu\n");

    do {
        // Prompt user for choice
        printf("\nEnter selection: ");
        fgets(input, sizeof(input) - 1, stdin);
        *(input + strlen(input) - 1) = '\0';
        token = strtok(input, " \t");

        // Error checking to see if nothing was entered
        //   Will prompt again if problem occurs
        if(!token) {
            choice = BLANK;
            printf("NOTHING WAS ENTERED\n");
            continue;
        }

        // Error checking to see if menu choices were only integers
        if(strspn(token, "0123456789") != strlen(token)) {
            printf("ONLY INTEGER VALUES ALLOWED\n");
            choice = BADLINE;
            continue;
        }

        // Error checking to see that menu choice was in acceptable range
        choice  = (int) strtol(token, (char **)NULL, 10);
        if(choice > 9 || choice < 0) {
            printf("Illegal menu selection!  Try again!\n");
            choice = BADLINE;
            continue;
        }

    } while(choice == BLANK || choice == BADLINE);
    return choice;
}

// Function that will be passed a copy of the current configuration and will prompt user for
//   their overlay and startBit pattern. It will return a new unsigned short that will
//   contain the overlay pattern.
unsigned short bitOverlay(unsigned short config) {
    int startBit;
    int overlay_length;
    char line[LINEMAX];
    char *token;
    bool inputInvalid = true;
    unsigned short overlay;
    unsigned short conf = config;

    do {
        // Prompt user for overlay pattern and starting bit
        printf("\nEnter overlay pattern and starting bit: ");
        fgets(line, LINEMAX, stdin);
        *(line + strlen(line) - 1) = '\0';

        // Error checking to see if nothing was entered
        if(!strlen(line))
        {
            printf("Nothing was entered\n");
            continue;
        }

        // Error checking to see if nothing was entered
        token = strtok(line, " \t");
        if(token == NULL)
        {
            printf("Nothing was entered\n");
            continue;
        }

        // Error checking to see if overlay pattern consists of only 1's and 0's
        if(strspn(token, "01") != strlen(token)) {
            printf("OVERLAY PATTERN MUST CONTAIN ONLY 1'S AND 0'S\n");
            continue;
        }

        overlay_length = strlen(token);
        overlay = (unsigned short) strtol(token, (char **)NULL, 2);

        // Error checking to see if starting bit was entered
        if((token = strtok(NULL, " \t")) == NULL) {
            printf("STARTING BIT NOT ENTERED\n");
            continue;
        }

        // Error checking to see that starting bit consists of only integers
        if(strspn(token, "0123456789") != strlen(token)) {
            printf("STARTING BIT MUST BE AN INTEGER\n");
            continue;
        }

        // Convert the startBit which is 
        startBit = (int) strtol(token, (char **)NULL, 10);

        // Error checking to see whether or not overlay pattern will be cut off
        if((startBit + overlay_length) > 16) 
            printf("%d VALUE(S) OF OVERLAY PATTERN WILL BE CUT OFF\n", startBit + overlay_length - NUMBITS);

        inputInvalid = false;
    } while(inputInvalid);

    conf &= ~(~((unsigned short) ~0 << overlay_length) << startBit);
    conf |=  overlay << startBit;
    return conf;
}

// function that will accept an unsigned short and will 
//   print it out to screen 
void printbits(unsigned short wrd)
{
    int i;
    for (i = 15; i >= 0; i--) {
        if(i == 10 || i == 4)
            printf(" %1d", testbit(wrd, i));
        else
            printf("%1d", testbit(wrd, i));
    }
    printf("\n");
    return;
}

int testbit(unsigned short wrd, int bit_to_test)
{
    wrd >>= bit_to_test;
    wrd &= 1;
    return wrd;
}

/* OUTPUT

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection:
NOTHING WAS ENTERED

Enter selection: 10
Illegal menu selection!  Try again!

Enter selection: abc
ONLY INTEGER VALUES ALLOWED

Enter selection: 0

Current light configuration
00000 000000 00000

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 2

Current light configuration
11111 000000 00000

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 3

Current light configuration
11111 111111 00000

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 4

Current light configuration
11111 111111 11111

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 5

Current light configuration
00000 111111 11111

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 6

Current light configuration
00000 000000 11111

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 7

Current light configuration
00000 000000 00000

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 1

Current light configuration
11111 111111 11111

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 8

Enter overlay pattern and starting bit: 1002 3
OVERLAY PATTERN MUST CONTAIN ONLY 1'S AND 0'S

Enter overlay pattern and starting bit: 10001 abc
STARTING BIT MUST BE AN INTEGER

Enter overlay pattern and starting bit:
Nothing was entered

Enter overlay pattern and starting bit:
Nothing was entered

Enter overlay pattern and starting bit: 1001 3

Current light configuration
11111 111110 01111

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 1

Current light configuration
11111 111111 11111

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 8

Enter overlay pattern and starting bit: 10001100101100111 4
5 VALUE(S) OF OVERLAY PATTERN WILL BE CUT OFF

Current light configuration
10010 110011 11111

=== Choose light configuration ===

0) turn off all lights
1) turn on all lights
2) turn on left stage lights (lights 11-15)
3) turn on center stage lights (lights 5-10)
4) turn on right stage lights (lights 0-4)
5) turn off left stage lights
6) turn off center stage lights
7) turn off right stage lights
8) overlay on/off pattern onto light configuration
9) quit the menu

Enter selection: 9

*/


