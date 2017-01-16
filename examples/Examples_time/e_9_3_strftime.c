/****************************************************************************
 
   Demonstration of the strtime function

****************************************************************************/
#include <stdio.h>
#include <time.h>

int main( void )
{
    struct tm *timeptr;
    time_t timeval;
    char buffer[80];

    time(&timeval);

    timeptr = localtime(&timeval);

    strftime(buffer, 80, "%c\n", timeptr);
    printf("strftime %%c format\n");
    printf("-------------------------\n %s\n", buffer);
    // Wed Mar 23 16:33:38 2016

    strftime(buffer, 80, "%A, %B %d, %H:%M\n", timeptr);e
    printf("strftime %%A, %%B %%d, %%H:%%M format\n");
    printf("--------------------------------\n %s\n", buffer);
    // Wednesday, March 23, 16:33

    strftime(buffer, 80, "%a, %b %d, %H:%M\n", timeptr);
    printf("strftime %%a, %%b %%d, %%H:%%M format\n");
    printf("--------------------------------\n %s\n", buffer);
    // Wed, Mar 23, 16:33

    strftime(buffer, 80, "%a, %b %d, %I:%M %p\n", timeptr);
    printf("strftime %%a, %%b %%d, %%I:%%M %%p format\n");
    printf("-----------------------------------\n %s\n", buffer);
    // Wed, Mar 23, 04:33 PM

    strftime(buffer, 80, "%a, %b %d, %I:%M %p, %Y\n", timeptr);
    printf("strftime %%a, %%b %%d, %%I:%%M %%p, %%Y format\n");
    printf("---------------------------------------\n %s\n", buffer);
    // Wed, Mar 23, 04:33 PM, 2016

    strftime(buffer, 80, "%a, %b %d, %I:%M %p, %y\n", timeptr);
    printf("strftime %%a, %%b %%d, %%I:%%M %%p, %%y format\n");
    printf("---------------------------------------\n %s\n", buffer);
    // Wed, Mar 23, 04:33 PM, 16

    strftime(buffer, 80, "%A, %b %d %I:%M %p %Y\n", timeptr);
    printf("strftime %%A, %%b %%d, %%I:%%M %%p, %%Y format\n");
    printf("---------------------------------------\n %s\n", buffer);
    // Wednesday, Mar 23 04:33 PM 2016

    return 0;
}

