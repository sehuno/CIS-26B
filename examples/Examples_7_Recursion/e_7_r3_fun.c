/************************************
	 What is the output?
*/

#include <stdio.h>

int main(void)
{
    void fun(int);
    int n = 234;
    //int n = 2345;

    fun(n);

    return 0;
}

/***********************************/
void fun(int n)
{
    if(n > 0)
    {
        printf( "%d", n % 10 );
		fun(n / 10);
    }
	printf("*\n");

    return;
}
