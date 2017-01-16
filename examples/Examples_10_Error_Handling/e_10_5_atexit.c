/****************************************************************************

   Demonstration of the atexit function

****************************************************************************/
// #include <windows.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define SLEEP for (j = 0; j < 16777510; j++)
int main( void )
{
    void handler(int signum);
    void cleanup(void);
    int j, k, *ptr = NULL;

    atexit(cleanup);
    signal(SIGSEGV, handler);

    for (k = 0; k < 8; k++)
    {
        //sleep(1);
        // Sleep(1000);
        SLEEP;
        if (k == 3)
            printf("%d\n", *ptr);

        printf("Ouch!\n");
    }
    return 0;
}

/**************************************************
*/
void handler(int signum)
{
    printf("Aborting due to SIGSEGV!\n");
    exit(1); // should cause cleanup to be called
}

/**************************************************
*/
void cleanup(void)
{
    printf("I'm in the exit handler!\n");
    return;
}


