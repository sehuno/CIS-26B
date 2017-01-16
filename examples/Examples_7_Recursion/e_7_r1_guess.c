/****************************************************************************
**
** RECURSION         GUESS A NUMBER - EXAMPLE
**
********************************************************

  The main goal of this example is to compare an iterative approach in
  solving a problem to a recursive one.

  This program generates a random number between 1 and 20 and then prompts
  the user to enter his/her guess up to 5 times.

****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20
#define MIN 1

int main ( void )
{
    void guess ( int random_num, int num_of_guesses );
    int random_num;
    int num_of_guesses = 5;

    srand( time( NULL ) );
    random_num = rand() % (MAX - MIN + 1) + MIN;

    guess( random_num, num_of_guesses );

    return 0;
}

/***************************************************
   ITERATIVE APPROACH
   Play the game up to num_of guesses times
*/
void guess(int random_num, int num_of_guesses)
{
    int num;

    while (num_of_guesses > 0){
        printf( "Enter a number: " );
        scanf( "%d", &num );

        if (num == random_num){
            printf("Congratulations! You did it!\n\n");
            return;
        }
        if (num_of_guesses == 1)
            printf("Sorry, the number was %d\n\n", random_num);
        else{
            if (num < random_num)
                printf("Your guess is low!");
            else
                printf("Your guess is high!");
            printf(" Try again!\n\n");
        }
        num_of_guesses--;
    }
    return;
}

/***************************************************
   RECURSIVE APPROACH
   Play the game up to num_of guesses times

void guess(int random_num, int num_of_guesses)
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num == random_num)
        printf( "Congratulations! You did it!\n\n" );
    else
        if (num_of_guesses == 1)
            printf("Sorry, the number was %d\n\n", random_num);
        else{
            if(num < random_num)
                printf("Your guess is low!");
            else
                printf("Your guess is high!");
            printf(" Try again!\n\n");
            guess(random_num, num_of_guesses - 1);
        }

    return;
}
*/
