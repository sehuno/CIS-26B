/****************************************************************************
 
   Using the ANSI C Time Functions

****************************************************************************/
#include <stdio.h>
#include <time.h>

int main( void )
{
    struct tm *timeptr; // Notice lack of allocation
    time_t timeval;
    char *chtime;       // No space allocation again!

    time(&timeval);     // seconds since 1/1/70
    printf("%ld\n", timeval);
    // 1458778182
    timeval = time(NULL);
    printf("%ld\n", timeval);
    // 1458778182

    timeptr = localtime(&timeval);
    printf("Local time: %d hours, %d minutes\n\n", 
        timeptr->tm_hour,
        timeptr->tm_min);
    //Local time: 17 hours, 9 minutes

    timeptr = gmtime(&timeval);
    printf("Greenwich time: %d hours, %d minutes\n\n", 
        timeptr->tm_hour,
        timeptr->tm_min);
    //Greenwich time: 0 hours, 9 minutes

    chtime = asctime(timeptr);
    printf("Greenwich ASCII time from asctime: %s\n\n", chtime);
    //Greenwich ASCII time from asctime: Thu Mar 24 00:09:42 2016

    timeptr = localtime(&timeval);
    chtime = asctime(timeptr);  
    printf("Local ASCII time from asctime: %s\n\n", chtime);
    //Local ASCII time from asctime: Wed Mar 23 17:09:42 2016

    // asctime takes a struct tm pointer
    // ctime takes a time_t pointer

    chtime = ctime(&timeval);
    printf("Local ASCII time from ctime: %s\n\n", chtime);
    // Local ASCII time from ctime: Wed Mar 23 17:09:42 2016
    
    return 0;
}

