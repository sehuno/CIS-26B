/*********************************************************
   CIS 26B -  Advanced C Programming
   Write a function named findMax that finds the maximum of
   any number of integer arguments. Use as a sentinel value 0.
   The first parameter is to represent one of the numbers.

   Extra Credit:
********************************************************/

#include <stdio.h>
#include <stdarg.h>

int findMax(int n, ...);

int main(void)
{
    printf("The largest is: %d\n", findMax(99, 20, 90, 10, 0));
    printf("The largest is: %d\n", findMax(40, 20, 10, 50, 30, 0));
    printf("The largest is: %d\n", findMax(25, 20, 10, 0));
    printf("The largest is: %d\n", findMax(10, 13, 0));
    printf("The largest is: %d\n", findMax(5, -20, 2, -50, -30, -90, 0));

    return 0;

}
/**
  Finds the maximum of any number of integer arguments.
*/

int findMax(int n, ...)
{
  int num, max;
  va_list argp;
  va_start(argp, n);
  max = num = n;
  while(num != 0)
  { 
    if(num > max)
      max = num;
    num = va_arg(argp, int);
  }
  va_end(argp);
  return max;
}