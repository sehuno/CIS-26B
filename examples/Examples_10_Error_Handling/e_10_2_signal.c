/****************************************************************************

   The signal function

****************************************************************************/
//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define SLEEP for (j = 0; j < 16777217; j++)

int main( void )
{
    void handler(int signum);

    float i, j, res;
    char line[80], *ptr = NULL;

    signal(SIGINT, handler);
    signal(SIGFPE, handler);
    signal(SIGSEGV, handler);

    for (i = 0; i < 8; i++)
    {
        //sleep(1);
        //Sleep(1000);  // windows
        SLEEP;
        printf("Ouch!\n");
    }
    printf("Enter two numbers: ");
    gets(line);
    sscanf(line, "%f %f", &i, &j); // 10 0

    if (j == 0)
        raise(SIGFPE);
    else
    {
        res = i / j;
        printf(" %f / %f = %f\n", i, j, res);
    }
    printf("\nptr has not been initialized: What happens if we dereference it?\n");
    printf("*ptr = %c\n", *ptr);

    return 0;
}

/**************************************************
   The signal handler function
*/
void handler(int signum)
{
    switch (signum)
    {
    case SIGINT:  printf("SIGINT caught!\n");
                  signal(SIGINT, handler); // refresh
                  break;
    case SIGSEGV: printf("SIGSEGV caught!\n");
                  printf("End of Program!\n");
                  getchar();
                  exit(1); // <-- must exit here: some functions are not re-entrant
                  break;
    case SIGFPE:  printf("SIGFPE caught!\n");
                  signal(SIGFPE, handler); // reinstallation of the signal handling is a must
                  break;
    }
    return;
}
