/****************************************************************************

   Demonstration of the perror function

****************************************************************************/
#include <stdio.h>  // perror
// #include <assert.h> // errno
#include <errno.h>
#include <stdlib.h> // strtol
#include <limits.h>

int main( void )
{
    char *string = "2222222222222222222222222222222222222222222222222222222";
    //char *string = "2122222222";
    long num;

    errno = 0;
    num = strtol(string, NULL, 10);
    if (errno)
    {
        printf("Error# %d ", errno);
        perror("strtol failure!");
        exit(1);
    }
    printf("%ld\n", num);
    printf("%d\n", INT_MAX);
    return 0;
}
