/****************************************************************************

   Controlled Re-Entry to Code Via setjmp and longjmp

****************************************************************************/
#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

int main( void )
{
    void fun(int num);
    int limit = 8, k;
    
    if (setjmp(env) != 0)
    {
        printf("Got here via longjmp!\n");
        printf("Value of k is: %d\n", k);
        limit = 3;
    }
    for (k = 1; k <= limit; k++)
    {
        printf("k = %d ", k);
        fun(k);
    }

    return 0;
}

/**************************************************
*/
void fun(int num)
{
    int j;
    for(j = 0; j < num; j++)
        putchar('*');
    putchar('\n');
    if (num == 5)
        longjmp(env, 1);
    return;
}
