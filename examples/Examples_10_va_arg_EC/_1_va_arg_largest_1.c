/*********************************************************
   CIS 26B -  Advanced C Programming
   Write a function named findMax that finds the maximum of
   any number of integer arguments.

   Extra Credit:
*********************************************************/

#include <stdio.h>
#include <stdarg.h>

int findMax(int n, ...);

int main(void)
{
    printf("The largest is: %d\n", findMax(3, 20, 90, 10));
    printf("The largest is: %d\n", findMax(4, 20, 10, 50, 30));
    printf("The largest is: %d\n", findMax(2, 20, 10));
    printf("The largest is: %d\n", findMax(1, 13));
    printf("The largest is: %d\n", findMax(5, -20, 10, -50, -30, -90));

    return 0;
}

int findMax(int n, ...)
{
  int i, num, max;
  va_list argp;
  va_start(argp, n);
  for(i = 0; i < n; i++)
  {
    num = va_arg(argp, int);
    if(i == 0)
      max = num;
    if(num > max)
      max = num;
  }
  va_end(argp);
  return max;
}