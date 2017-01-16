/**********************************************
   Fibonacci: Recursive versus Iterative
*********************************************/

#include <stdio.h>

int main ( void )
{
    int fibonacci(int num);
    int num;
    char line[80];
    int res;

    while (printf("Enter an integer: "),
           gets(line),
           sscanf(line, "%d", &num),
           num != -1) // try 40
    {
        printf("Fibonacci number %d is: %d\n", num, fibonacci(num));
    }
    return 0;
}

/*********************************************
  ITERATIVE:
  Calculate Fibonacci
*/
int fibonacci(int num)
{
    int curr = 1, prev = 0, sum;

    if (num == 0 || num == 1) return num;
    num--;
    while (num--)
    {
        sum = curr + prev;
        prev = curr;
        curr = sum;
    }
    return sum;
}

/*********************************************
  RECURSIVE:
  Calculate Fibonacci

int fibonacci(int num)
{
    if (num == 0 || num == 1) return num;
    return fibonacci(num - 1) + fibonacci(num - 2);
}
*/
