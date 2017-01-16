/*

Extra Credit

Write a program that finds the largest prime number less than a given number. 
Implement a variation of the Sieve of Eratosthenes’s algorithm that uses bit manipulation. 

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {false, true} bool;

#define LIMIT 1500000 /*size of integers array*/
#define PRIMES 100000 /*size of primes array*/
#define SIZE 100

#define LEFT_SHIFT(intVal) (intVal << 2)

int main(){
	int i, j;
	char line[SIZE];
	int upperLimit;
	int numPrimes = 0;
	bool isValidInput;

	printf("PROGRAM TO FIND THE LARGEST PRIME NUMBER LESS THAN A GIVEN INTEGER.\n");
	do 
	{
		isValidInput = true;
		printf("\nEnter the upper, number limit: ");
		fgets(line, SIZE, stdin);

		if(*(line + strlen(line) - 1) == '\n')
			*(line + strlen(line) - 1) = '\0';
		if(!strlen(line)) {
			printf("Nothing was entered.\n"); 
			isValidInput = false;
			continue;
		}

		for(i = 0; i < strlen(line); i++)
		{
			if(!isdigit(line[i])) {
				printf("Not a valid input, must be all digits.\n");
				isValidInput = false;
				break;
			}
		}
	} while(!isValidInput);

	upperLimit = atoi(line);

	int intArr[LIMIT];
	int primesArr[PRIMES];
	for(i = 0; i < upperLimit; i++) 
		intArr[i] = i + 2;
	for(i = 0; i < upperLimit; i++)
		if(intArr[i] != -1)
			for(j = LEFT_SHIFT(intArr[i]) - 2; j < upperLimit; j += intArr[i])
				intArr[j] = -1;

	for(i = 0; i < upperLimit; i++)
		if(intArr[i] != -1)
			primesArr[numPrimes++] = intArr[i];

	printf("\nLargest prime is: %d", primesArr[numPrimes-1]);

	return 0;
}

/* 	output

PROGRAM TO FIND THE LARGEST PRIME NUMBER LESS THAN A GIVEN INTEGER.

Enter the upper, number limit: 123413

Largest prime is: 123407

*/