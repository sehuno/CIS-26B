/*********************************************************************************
** CIS 26B													    Winter, 2016
** Advanced C
******************
**
** Homework 1:
**        Arrays, Pointers, Strings, Structures, Sorting, and
**        Dynamic Allocation of Memory
**
**********************************************************************************

   Create and process arrays of structures: select students taking 22B & 22C.
 
   Save the output as a comment at the end of the program!
**********************************************************
**
**  Written By:  Sehun Oh         // <-- write your name here
**
**  Date: 1/8/2016                 // <-- write the date here
**  IDE (compiler): gcc  
**  Operating System: Mac OS X El Capitan=
***************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  

#define FLUSH while( getchar() != '\n' )

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

// STUDENT struct
typedef struct student
{
	char   name[31];
    int    id;
} STUDENT;

// Function Prototypes
void readFileNames(char *file1, char *file2, char *outName);
STUDENT* readFromFile(FILE *fData, char *file);
void sortStudentArray(STUDENT* studArr);
void displayStudentArray(STUDENT* studArr);
STUDENT* unionOfClasses(STUDENT *arr1, STUDENT *arr2, int *numStuds);
void writeToFile(FILE *outfile, STUDENT* studArr, int *numStuds, char* outName);
void swap (STUDENT* a, STUDENT* b);

int main( void )
{
    #ifdef _MSC_VER 
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n"); 
    #endif 

    FILE *f1Data, *f2Data, *fOutData;               // FILE pointer for two input files and one output
    STUDENT *class1, *class2, *studentsInBoth;      // STUDENT pointers for dynamic allocation of STUDENT structs
    int numInBoth;          // Number of students in both classes   
    char file1[300];        // File path for first file
    char file2[300];        // File path for second file
    char outName[300];      // File path for output file

    // Read in file names
    readFileNames(file1, file2, outName); 

    // Read in from files
    class1 = readFromFile(f1Data, file1); 
    class2 = readFromFile(f2Data, file2); 

    // Sort the student array according to ID
    sortStudentArray(class1);
    sortStudentArray(class2);

    // Display sorted arrays
    printf("Sorted list of first class: \n");
    displayStudentArray(class1);
    printf("\nSorted list of second class: \n");
    displayStudentArray(class2);

    // Find students in both classes while sorting them in ascending order for id
    studentsInBoth = unionOfClasses(class1,class2, &numInBoth);

    // Write the list to the output file
    writeToFile(fOutData, studentsInBoth, &numInBoth, outName);

    // Free dynamically allocated memory
    free(class1);
    free(class2);
    free(studentsInBoth);

    return 0;
}

/* 
    The readFileNames function will prompt the user for the proper file paths
    of input files.
*/
void readFileNames(char *file1, char *file2, char *outName) 
{
	char read1[300];
    char read2[300];
    char out[50];
    char outRead[300];

    printf("Please enter the filepath to first input file: ");
    fgets(read1, sizeof(read1), stdin);
    *(read1 + strlen(read1) - 1) = '\0';

    printf("Please enter the filepath to second input file: ");
    fgets(read2, sizeof(read2), stdin);
    *(read2 + strlen(read2) - 1) = '\0';

    printf("Please enter the desired name for the output file: ");
    fgets(out, sizeof(out), stdin);
    *(out + strlen(out) - 1) = '\0';
    if(strcmp(out,"")==0) { 
        printf("No name specified. Used name will be \"out.txt\" in the same folder as input files.\n");
        strcpy(out, "out.txt");
    }

    if(strcmp(read1,"")==0) {
        printf("\nPlease enter the filepath to default file of in26Btxt: ");
        fgets(read1, sizeof(read1), stdin);
        *(read1 + strlen(read1) - 1) = '\0';
    }

    if(strcmp(read2,"")==0) {
        printf("Please enter the filepath to default file of in22Ctxt: ");
        fgets(read2, sizeof(read2), stdin);
        *(read2 + strlen(read2) - 1) = '\0';
    }

    // Prepping for proper filepath of output file by
    //  finding delimiter at end which are either forward or back slash
    char *ptr = strrchr(read1, '\\');
    if(ptr == NULL) 
        ptr = strrchr(read1, '/');
    strncpy(outRead,  read1, strlen(read1) - strlen(ptr) + 1);
    strcat(outRead, out);

    // Copy read in strings
    strncpy(file1, read1, 300);
    strncpy(file2, read2, 300);
    strncpy(outName, outRead, 300);
}

/* 
The readFromFile function will take in a FILE pointer and a c-string and
    return a pointer to a dynamically allocated array of STUDENT objects.
*/
STUDENT* readFromFile(FILE *fData, char *file) 
{
    char line[100];
    char studName[31];
    int numStudents;
    char ch_id[4];
 	int i_id;
    int count = 0;

    // Perform validation for successful file open operation
    if((fData = fopen(file,"r")) == NULL) 
    {
    	printf("Error opening file at location %s!", file);
    	exit(101);
    }	

    // Reads first line of file to find the number of students in list
    fgets(line, sizeof(line), fData);
    numStudents = atoi(line);

    // Dynamically allocates one additional than required for array
    STUDENT* studArr = (STUDENT *)malloc((numStudents + 1) * sizeof(STUDENT));
    if(!studArr) 
    {
        printf("Error in dynamic allocation of memory when reading from file.\n");
        exit(201);
    }

    // Until end of line, read each line and get the id number and name.
    //  - Perform string parsing to remove newlines
	while (!feof(fData))
	{
	    fgets(line, sizeof(line), fData); 
	    i_id = atoi(strncpy(ch_id,line,4));
	    strncpy(studArr[count].name, line+5, strlen(line+5));
        if(*(studArr[count].name + strlen(studArr[count].name) - 1) == '\n')
            *(studArr[count].name + strlen(studArr[count].name) - 1) = '\0';
        studArr[count].id = i_id;
	    count++;
	}

    // To mark the last item, create a dummy student with a blank name and id of 0
    strcpy(studArr[count].name,"");
    studArr[count].id = 0;

    // Close file
	fclose(fData);

    // Return the pointer
    return studArr;
}

/* 
    The sortStudentArray function takes in a dynamically allocated array of STUDENTs
    and sorts the array using insertion sort in ascending order for student id.

*/
void sortStudentArray(STUDENT* studArr) 
{
    STUDENT* top = studArr;
    STUDENT* current;
    STUDENT* hold;

    // While the last has not yet been reached
    while(top->id != 0) {
        hold = top;
        current = hold + 1;
        while(current->id != 0) 
        {
            // if consequent student has a higher id, swap student
            if(current->id < hold->id)      
                swap(current, hold);
            current++;
        }
        top++;
    }
}

/* 
The displayStudentArray function will take in a student array and 
    display each of the student's attributes
*/
void displayStudentArray(STUDENT* studArr) 
{
    // If array is empty, print NULL
    if (studArr == NULL)
    {
        printf("NULL\n");
        exit(102);
    }
    
    // For each student in array, print their information
    int i;
    for(i = 0; studArr[i].id != 0; i++)
        printf("%d %s\n", studArr[i].id, studArr[i].name);
}

/* 
The displayStudentArray function will take in a student array and 
    display each of the student's attributes
*/
STUDENT* unionOfClasses(STUDENT *arr1, STUDENT *arr2, int *numStuds) 
{
    STUDENT *l1ptr = arr1; 
    STUDENT *l2ptr = arr2; 
    int numStudents = 0; 
    int space = 2; 
    int i = 0; 
    int j = 0; 

    // Dynamically allocate an array of STUDENT structs and print an error message when dynamic allocation failed.
    STUDENT *both = (STUDENT *)malloc(2 * sizeof(STUDENT)); 
    if(!both) 
    {
        printf("Error in dynamic allocation of memory when creating mathematical union of students in classes.\n");
        exit(200);
    }

    // While either of the STUDENT arrays have not yet reached its end, do the loop
    while(l1ptr[i].id != 0 && l2ptr[j].id != 0) 
    {
        // If the id and name of the STUDENT structs are the same, do the loop
        if(l1ptr[i].id == l2ptr[j].id && (strcmp(l1ptr[i].name, l2ptr[j].name) == 0))
        {
            // If there is not enough space in the array, do the loop.
            if(numStudents >= space) 
            {   
                space *= 2;     // double the space
                both = (STUDENT *)realloc(both, space * sizeof(STUDENT));   // dynamically allocated double the space
                // If dynamic allocation fails print alert messge
                if(!both) 
                {
                    printf("Error when using realloc for students in both classes\n");
                    exit(202);
                }
            }
            // Copy STUDENT attributes to the union array
            (both + numStudents)->id = l1ptr[i].id;
            strncpy((both+numStudents)->name, l1ptr[i].name, sizeof(l1ptr[i].name));
            numStudents++;
            i++;
            j++;
        }
        else if (l1ptr[i].id < l2ptr[j].id)     // Increment first list pointer
            i++; 
        else                                    // Increment second list pointer
            j++;            
    } 
    // Add a dummy student struct at the end of list to mark the list end
    strcpy((both+numStudents)->name,""); 
    (both+numStudents)->id = 0; 

    // Store number of students into the main variable
    *numStuds = numStudents;

    // Return the pointer
    return both; 
} 

/* 
    The writeToFile function will take in the output FILE, the array of students in both classes,
        the number of students in both classes and will print to the output file the list of students
        in both classes, with the same formatting.
*/
void writeToFile(FILE *outfile, STUDENT* studArr, int *numStuds, char* outName) 
{
    // Perform validation for opening file to write
    if((outfile = fopen(outName,"w")) == NULL)
        printf("Error creating output file!\n");

    // For each student print their information to file
    int i;
    fprintf(outfile, "%d\n", *numStuds);
    for(i = 0; studArr[i].id != 0; i++)
        fprintf(outfile, "%d %s\n", studArr[i].id, studArr[i].name);

    fclose(outfile);
}

/* 
    The swap function will swap two STUDENT structs by swapping their attributes.
*/
void swap (STUDENT* a, STUDENT* b) 
{
    STUDENT temp;

    temp.id = a->id;
    a->id = b->id;
    b->id = temp.id;

    strncpy(temp.name, a->name, 31);
    strncpy(a->name, b->name, 31);
    strncpy(b->name, temp.name, 31);

    return;
}


/* OUTPUT 
Please enter the filepath to first input file:
Please enter the filepath to second input file:
Please enter the desired name for the output file:
No name specified. Used name will be "out.txt" in the same folder as input files.

Please enter the filepath to default file of in26Btxt: /Users/sehun/Documents/26b/hw1/in26B.txt
Please enter the filepath to default file of in22Ctxt: /Users/sehun/Documents/26b/hw1/in22C.txt
Sorted list of first class:
1189 Shmoys, David
1234 Marley, Tom
2901 Green, Mary
2908 Vigoda, Eric
3456 Karlin, Anna
4344 Kelley, Sandra
5445 Homer, Steve
5567 Welch, Jennifer
6566 Williams, Ryan
6579 Vadhan, Salil
6766 Hemaspaandra, Lane
8372 Chen, Li
8433 Chakrabarti, Amit
8879 Bein, Wolfgang
8999 Fenner, Mia
9002 Khuller, Samira
9123 Vianu, Victor
9865 Beame, Paul

Sorted list of second class:
1111 Tan, Li-Yang
2000 Barenboim, Leonid
2001 Rossman, Marie
3456 Karlin, Anna
3728 Sipos, Claudine
3732 Wire, Oralee
4344 Kelley, Sandra
5445 Homer, Steve
5511 Welch, Claire
6009 Mumey, Brendan
6577 Green, Susan
6666 Forbes, Michael
8433 Chakrabarti, Amit
8800 Servedio, Rocco
8999 Fenner, Mia
9123 Vianu, Victor
9865 Beame, Paul

*/ 

/*

file output for out.txt:
6
3456 Karlin, Anna
4344 Kelley, Sandra
5445 Homer, Steve
8433 Chakrabarti, Amit
8999 Fenner, Mia
9123 Vianu, Victor

*/

/* OUTPUT 2 
Please enter the filepath to first input file: /Users/sehun/Documents/26b/hw1/in1a.txt
Please enter the filepath to second input file: /Users/sehun/Documents/26b/hw1/in1b.txt
Please enter the desired name for the output file: 1a1b.txt
Sorted list of first class:
1234 Bull, Maddie
1238 Weisgerber, Leif
1293 Rennie, Jarvis
1298 Encinas, Margarette
1918 Number, Deanne
2093 Tester, Louanne
2934 Pichon, Bert
3623 Gillie, January
4762 Caruana, Kandice
7432 Piermarini, Lynda
7439 Yochum, Sterling
8324 Surette, Classie
8324 Daily, Sherley
8473 Tignor, Marina
8732 Quan, Particia
9482 Kuzma, Cathie

Sorted list of second class:
1298 Encinas, Margarette
2371 Acy, Raphael
2372 Sancho, Terrell
3277 Hinkson, Ileen
3283 Hajduk, Keesha
3612 Hutchcraft, Patsy
3623 Gillie, January
3728 Sipos, Claudine
3732 Wire, Oralee
4613 Mccreery, Trudy
4623 Tweedy, Twinkie
4762 Caruana, Kandice
4772 Pinkard, Twila
4827 Richman, Lily
4872 Lucca, Aracelis
7439 Kiser, Zachary
8324 Surette, Classie
9323 Dewolf, Elfriede
*/

/* FILE OUTPUT 1a1b.txt 
4
1298 Encinas, Margarette
3623 Gillie, January
4762 Caruana, Kandice
8324 Surette, Classie
*/