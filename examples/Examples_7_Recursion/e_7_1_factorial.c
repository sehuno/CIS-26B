/**********************************************
   Factorial: Recursive versus Iterative
*********************************************/

#include <stdio.h>

int main ( void )
{
    long fact(int num);
    int num;
    char line[80];

    while (printf("Enter an integer: "), gets(line), sscanf(line, "%d", &num), num != 0)
    {
        printf("The factorial of %d is %ld\n", num, fact(num));
    }
    return 0;
}

/*********************************************
  ITERATIVE:
  Calculate factorial
*/
long fact(int num)
{
    long total = 1;
    char line[80];

    while (num) total *= num--;
    return total;
}


/*********************************************
  RECURSIVE:
  Calculate factorial

long fact(int num)
{
    if (num == 1) return 1;
    return num * fact(num - 1);
}
*/
