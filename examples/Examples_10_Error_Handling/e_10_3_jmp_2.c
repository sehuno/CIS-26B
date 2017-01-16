/****************************************************************************

   Controlled Re-Entry to Code Via setjmp and longjmp

****************************************************************************/
// #include <windows.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#define SLEEP  for (j = 0; j < 16777510; j++)

jmp_buf env;

int main( void )
{
    void handler(int signum);
    int j, k;

    signal(SIGINT, handler);
    if (setjmp(env) != 0)
    {
        printf("Got here via longjmp!\n");
        printf("Value of k is: %d\n", k);
    }
    signal(SIGINT, handler);
    for (k = 0; k < 8; k++)
    {
        // sleep(1);
        // Sleep(2000);
        SLEEP;
        printf("Ouch!\n");
    }
    return 0;
}

/**************************************************
   The signal handler function
*/
void handler(int signum)
{
    printf("SIGINT caught!\n");
    signal(SIGINT, handler);
    longjmp(env, 1);
}
