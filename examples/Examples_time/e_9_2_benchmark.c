/****************************************************************************

   Program Benchmarking Using Gmtime and Difftime

****************************************************************************/
#include <stdio.h>
#include <time.h>

int fibonacci(int num);

int main( void )
{
    int fibonacci_term, term_no;
    double ftime;
    time_t time1, time2, diff;
    struct tm *tptr;

    term_no = 42;
    time(&time1);
    fibonacci_term = fibonacci(term_no);
    time(&time2);

    diff = time2 - time1;
    tptr = gmtime(&diff);
    printf("Calculating term#%d = %d took %d seconds!\n\n", term_no, fibonacci_term, tptr->tm_sec);

    ftime = difftime(time2, time1);
    printf("Calculating term#%d = %d took %.0f seconds!\n\n", term_no, fibonacci_term, ftime);

    return 0;
}


/*********************************************
  ITERATIVE:
  Calculate Fibonacci

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
*/
/*********************************************
  RECURSIVE:
  Calculate Fibonacci
*/
int fibonacci(int num)
{
    if (num == 0 || num == 1) return num;
    return fibonacci(num - 1) + fibonacci(num - 2);
}


