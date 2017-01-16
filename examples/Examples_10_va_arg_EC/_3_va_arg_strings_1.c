/*********************************************************
   CIS 26B -  Advanced C Programming
   Write a function named display that takes any number of arguments.
   The first argument must be an integer.
   The remaining arguments will be strings.
   The first argument specifies the number of strings.

   Extra Credit:
*********************************************************/

#include <stdio.h>
#include <stdarg.h>

void display(int n, ...);

int main(void)
{
    display(5, "one", "two", "three", "four", "five");
    display(2, "dog", "cat");
    display(4, "dog", "cat", "mouse", "bird");
    display(3, "cat", "mouse", "bird");
    return 0;

}


void display(int n, ...)
{
  int i;
  char *word;
  va_list argp;
  va_start(argp, n);
  for(i = 0; i < n; i++) {
    word = va_arg(argp, char *);
    printf("%s ", word);
  }
  printf("\n");
}
