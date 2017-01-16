/*********************************************************
   CIS 26B -  Advanced C Programming
   Write a function named findAvg that finds the average of
   of the integer arguments. It also displays the parameters
   greater than or equal to the average.

   Eztra Credit:
*********************************************************/

#include <stdio.h>
#include <stdarg.h>

double findAvg(int n, ...);

int main(void)
{
    printf("The average is: %.1f\n", findAvg(3, 20, 90, 10));
    printf("The average is: %.1f\n", findAvg(4, 20, 10, 50, 31));
    printf("The average is: %.1f\n", findAvg(2, 22, 13));
    printf("The average is: %.1f\n", findAvg(1, 13));
    printf("The average is: %.1f\n", findAvg(5, -20, 11, -53, -30, -90));

    return 0;

}

double findAvg(int n, ...) 
{
  int i;
  double avg;
  va_list argp;
  va_start(argp, n);
  for(i = 0; i < n; i++) 
    avg += va_arg(argp, int);
  va_end(argp);
  return avg / (double) n;
} 