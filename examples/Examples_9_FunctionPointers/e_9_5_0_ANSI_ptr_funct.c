/****************************************************************************

   Demonstration of Old (Pre-ANSI)Style Pointers to Functions

****************************************************************************/
#include <stdio.h>

int main( void )
{
    double reciprocal(int);
    double square(int);
    //double sum(int, double (*f)(int));
    double sum(int, double f(int));

    printf("Sum of 5 reciprocals: %f\n", sum(5, reciprocal));
    printf("Sum of 3 squares: %f\n",     sum(3, square));

    return 0;
}

/*****************************************************
  sum
*/
//double sum(int n, double (*f)(int))
double sum(int n, double f(int))
{
    double sum = 0;
    int i;

    for (i = 1; i <= n; i++)
        sum += f(i);
    return sum;
}

/*****************************************************
  reciprocal
*/
double reciprocal(int k)
{
    return 1.0 / k;
}

/*****************************************************
  square
*/
double square(int k)
{
    return k * k;
}

/**
Sum of 5 reciprocals: 2.283333
Sum of 3 squares: 14.000000
*/
