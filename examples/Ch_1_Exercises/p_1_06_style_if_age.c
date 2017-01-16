/***************************************************
    Exercise 1.6
    Rewrite the following program using optimal C coding style.
    Pay attention to:
    - white spaces and indentation
    - short-cut boolean expressions in if or loop statements
    - use the ternary operator
    - code redundancy
    - proper use of the relational expression in a return statement
    - use of the comma operator in a loop
    - use of && and || to prevent if nesting

    Name:
    Date:
/***************************************************/
#include <stdio.h>

struct date
{
    int month;
    int day;
    int year;
};

int main (void)
{
    int calcAge(struct date b, struct date c);
    struct date bdate = {6, 22, 1980};
    //struct date bdate = {3, 22, 1980};
    //struct date bdate = {4, 22, 1980};
    //struct date cdate = {4,  1, 2011};
    struct date cdate = {4, 23, 2011};

    printf("Your age is %d is ", calcAge(bdate, cdate));

    return 0;
}
/***************************************************
    Calculate the age of a person in years
*/
int calcAge(struct date b, struct date c)
{
    int age = c.year - b.year;

    if (b.month > c.month)
        age--;
    else
        if (b.month == c.month && b.day > c.day)
                age--;
    return age;
}

/** SAVE THE OUTPUT BELOW

*/
