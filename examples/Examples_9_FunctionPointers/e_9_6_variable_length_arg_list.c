/****************************************************************************
   Functions with Variable-Length Argumet Lists
   Two Examples: sumargs()
                 char_find()
****************************************************************************/
#include <stdio.h>
#include <string.h>

#include <stdarg.h>  // va_list, va_start(), va_arg(), va_end()

int main( void )
{
    double sumargs(int n, ...);
    void   char_find(char *, ...);

    double x = 20.0;
    int    a = 10;
    char   c = 'A';


    // n - how many unnamed arguments follow
    printf("Sum of three argumetns is %f\n",
           sumargs(3, 10.0, 20.0, 30.0));
           //sumargs(3, 10, 20, 30));
    printf("Sum of two argumetns is %f\n",
           //sumargs(2, 10.0, 20.0));
           sumargs(2, 10, 20));

    printf("Sum of ZERO argumetns is %f\n\n",
           sumargs(0));

    // INCORRECT
    //printf("Sum of THREE arguments of different types is %f\n\n",
      //     sumargs(3, a, x, c ));

    // CORRECT
    printf("Sum of THREE arguments of different types is %f\n\n",
         sumargs(3, (double)a, x, (double)c ));

    // char_find() uses # as a sentinel to warn that
    // it is the final unnamed argument
    char_find("Hello", 'e', 'l', 'i', 'k', 'o', '#');

    return 0;
}
/**************************************************
   Sum all the unnamed arguments.
   First argument tells function how many
   unnamed arguments follow
*/
double sumargs(int n, ...)
{
    va_list argp;
    double sum = 0.0;

    // va_start() initializes argp to point at the first
    // unnamed argument after the last named argument
    va_start(argp, n);


    while (n--)
    {
        sum += va_arg(argp, double);
               // get the current argument
               // move argp to the next unnamed argument
    }

    va_end(argp); //to free the nodes of the unnamed argument list
    return sum;
}

/**************************************************
   Report whether unnamed char constant arguments
   are in string or not.
   It uses # as a sentinel to warn that it is the
   final unnamed argument
*/
void   char_find(char *string, ...)
{
    va_list argp;
    char c;

    va_start(argp, string);
    //while ((c = va_arg(argp, char)) != '#') // int VS char!!!
    while ((c = va_arg(argp, int)) != '#') // int VS char!!!
    {                                      // char and short are promoted to int!
        printf("The character %c is%s in %s\n",
            c, strchr(string, c) ? "": " not", string);
    }
    va_end(argp);
    return;
}
/**
Sum of three argumetns is 60.000000
Sum of two argumetns is 30.000000
Sum of ZERO argumetns is 0.000000

Sum of THREE arguments of different types is 95.000000

The character e is in Hello
The character l is in Hello
The character i is not in Hello
The character k is not in Hello
The character o is in Hello
*/
