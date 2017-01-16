/****************************************************************************

   Timing Programs Out with SIGALRM
   // SIGALRM is not part of the ANSI C, but many compilers have it

****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main( void )
{
    void myalarm(void);
    int num;

    signal(SIGALRM, myalarm);

    alarm(5);
    printf("You have 5 seconds to enter a number! ");
    scanf("%d", &num);
    alarm(0); // turn off the alarm clock
    printf("Good kid-you did it!\n");
    // getchar();
    return 0;
}

/**************************************************
   The myalarm() function
*/
void myalarm(void)
{
    printf("User is timed out!\n");
    exit(1);
}
