/************************************************************
    Examples: 4.7a strtol convertion of user input to integer
/************************************************************/

#include <stdio.h>
#include <stdlib.h> // strtol
#include <errno.h>
#include <math.h>  // HUGE_VAL

int main (void)
{
    //char s[] = "8154";
    //char s[] = "81Q45M3";
    //char s[] = "R1Q45M3";
    char s[] = "9012345678";
    char *end;
    long num = -1;

    printf("Converting \"%s\" to a long using sscanf:\n\n", s);
    if (sscanf(s, "%ld", &num) == 1)
        printf("%ld\n\n", num);   // 8154
    else
        printf("%s not a number!\n\n", s);

    printf("Converting \"%s\" to a long using strtol:\n\n", s);
    num = -1;
    errno = 0;
    num = strtol(s, &end, 10);

    if (*end == '\0')
        printf("%ld\n\n", num);
    else
    {
        printf("%s NOT A NUMBER: it contains %c!\n\n", s, *end);
        printf("%ld\n\n", num);
    }
    if (errno == ERANGE)
    {
        printf("HUGE_VAL is %ld\n\n", (long)HUGE_VAL);
        printf("%s is greater than \n%ld!\n\tToo big to fit in a long!\n", s, num);
    }
    return 0;
}
