/**********************************************
   Read and validate a positive integer number:
*********************************************/

#include <stdio.h>

int main ( void )
{
    int getNum(void );
    int num;

    num = getNum();
    printf("%d\n", num);

    return 0;
}

/*********************************************
  ITERATIVE:
  Read and validate an integer:
  it must be positive

int getNum(void )
{
    int num, ioRes;
    char line[80];

    while (printf("Enter an integer: "),
           gets(line),
           sscanf(line, "%d", &num),
           num <= 0)
    {
       printf("Incorrect input!\n");
    }
    return num;
}
*/

/*********************************************
  RECURSIVE:
  Get and validate an integer:
  it must be positive
*/
int getNum(void )
{
    int num, ioRes;
    char line[512];

    if (printf("Enter an integer: "),
           gets(line),
           (ioRes = sscanf(line, "%d", &num)),
           (ioRes != 1 || num <= 0))
    {
       printf("Incorrect input!\n");
       num = getNum();
    }
    return num;
}

