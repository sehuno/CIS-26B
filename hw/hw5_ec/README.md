ASSIGNMENT: Homework 5
	"Binary Search Trees and Queues"

NAME: Sehun Eric Oh
UID: 20164293
CLASS: 26B, Winter 2016



FILES INCLUDED IN FOLDER:
 - tree.h, tree.c
 - queue.h, queue.c
 - write.h, write.c
 	write.c, function writeToFile will contain the line of code that sets the name of the output file.
 	* can be changed to desired output file name *

 - main.c
	contains the main function

 - input.c , sample_output.txt
 	this file was the original file that was used as the input file 
 		to create the cross reference listing in sample_output.txt 

 - output.txt
 	this file was created by me using my program with the input.c file

 - output1.txt
 	this cross reference file was created by using the program on the main.c file as the input file

 - makefile
 	the makefile to be able to call the make function to build the program

 	* can be edited to use the input file desired rather than the input.c file *






*Assumption that you are in puttY or a unix terminal*
- To build the program, run the command	

	make

- To run the program with the provided "input.c" as input file, run the command

	make run

- To run the program with custom input file, run the commands

	make
	./hw5 FILEPATH 		*NOTE* use absolute filepath


	**NOTE** output file called "output.txt" will be created within the directory that this program is called in.

- To clear all build, run the command
	
	make clean



*ADDITIONAL IMPLEMENTATION DETAILS*
- variable/token names starting with numbers have not been accounted for; underscore within the name is however taken care of.
- for input files containing more than 99 lines will be slightly, incorrectly formatted
- for input files containing tokens longer than 23 characters will be incorrectly formatted


PERSONAL NOTE:

Although this method of implementation for parsing line character by character may not be the most efficient, it is a method of input parsing/processing that I have not quite yet done so I considered this homework as a learning opportunity since I have used advanced string manipulation functions in all other homeworks. Reading in character by character from file is also a new frontier for me, set aside for the future. This implementation still read in file line by line using the fgets function.








