/****************************************************************************

   Controlled Re-Entry to Code Via setjmp and longjmp

****************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;

int main( void )
{
    void handler(int signum);
    int k, *ptr = NULL;

    signal(SIGSEGV, handler);

    if (setjmp(env) != 0)
    {
        printf("Got here via longjmp!\n");
        printf("Value of k is: %d\n", k);
        getchar();
        ptr = &k;
    }
    for (k = 0; k < 8; k++)
    {
        printf("k = %d\n", k);
        if (k == 3)
           printf("\tk = %d *ptr = %d\n", k, *ptr);
    }

    return 0;
}

/**************************************************
   The signal handler function
*/
void handler(int signum)
{
    printf("SIGSEGV caught!\n");
    signal(SIGSEGV, handler);
    longjmp(env, 1);
}
