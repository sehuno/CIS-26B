/************************************************************
    Examples: 4.7b strtod convertion of user input to double
/************************************************************/

#include <stdio.h>
#include <stdlib.h> // strtod

int main (void)
{
    //char s[] = "8.99";
    //char s[] = "8.1Q45M3";
    //char s[] = "R1Q4.5M3";
    //char s[] = "9012345678";
    //char s[] = "90123.45678";
    char s[] = "0.90123";

    char *end;
    double num;

    printf("Converting \"%s\" to a double using strtod:\n\n", s);

    num = strtod(s, &end);
    if (*end == '\0')
        printf("%f\n\n", num);
    else
    {
        printf("%s NOT A NUMBER: it contains %c!\n\n", s, *end);
        printf("%f\n\n", num);
    }

    return 0;
}
