/*
CIS 26B - Advanced C Programming
Homework #3
Sehun Eric Oh

Dealing with hashed file for a weather data base using binary file input output.
Also deals with advanced string manipulation of record and error checking

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef enum { false, true } bool;

#define MAXLINE    512
#define BUCKETS    100
#define BUCKETSIZE 240
#define RECORDSIZE 60
#define CITYMAX    49
#define RECS_PER_BUCKET 4
#define BLANK    -1
#define BADLINE  -2
#define GOODADD  -3
#define BADFILE  -4
#define NOTFOUND -5
#define FOUND    -6
#define ADD       1
#define LOOKUP    2
#define QUIT      3

#define FILENAME "hw3.dat"


// Function prototypes
FILE *openWeatherFile(void);
int addRecordsToDB(FILE *fp);
int lookupRecord(FILE *fp);
int menu(void);
bool setFilePointer(char *city_state, FILE* fp, int add_or_lookup);
long hash (char *key);

int main()
{    
    FILE *fp;
    int result, option;

    fp = openWeatherFile();
    while ((option = menu()) != QUIT)
    {
        switch (option)
        {
            case BADLINE:
            case BLANK:
                continue;
            case ADD:
                while ((result = addRecordsToDB(fp)) == BADLINE
                       || result == BADFILE);
                break;
            case LOOKUP:
                while ((result = lookupRecord(fp)) == BADLINE
                       || result == NOTFOUND) ;
                break;
        }
    }
}

// The openWeatherFile function will return a file pointer to a binary hashed file.
FILE *openWeatherFile(void)
{
    FILE *fp;
    char record[61];
    int i;
    
    // open hashed file
    fp = fopen(FILENAME, "w+b");
    
    for (i = 0; i < 59; i++) record[i] = ' ';
    record[59] = '\n';
    record[60] = '\0';
    
    for (i = 0; i < 400; i++) fprintf(fp, "%s", record);
    return fp;
}

// The addRecordsToDB will take in a file pointer and will return the corresponding
//  return values which indicate whether or not the add was successful.
int addRecordsToDB(FILE *fp)
{
    char file[MAXLINE];
    char rec[RECORDSIZE];
    char detect[RECORDSIZE];
    char city_state[CITYMAX];
    char *secondComma;
    int new_length, i;
    FILE *inputFile;

    // Input file prompt 
    printf("\nEnter filename: ");
    fgets(file, MAXLINE - 1, stdin);

    // when nothing is entered
    if(file[strlen(file)-1] == '\n' && strlen(file) == 1) 
        return BLANK;
    
    // change the last character
    *(file + strlen(file) - 1) = '\0';
    
    // Input file validation
    // // char fpath[50] = "/Users/sehun/Documents/26b/hw3/input";
    // // if ((inputFile = fopen(fpath, "r")) == NULL)
    if ((inputFile = fopen(file, "r")) == NULL)
    {
        printf("Batch insertion file could not be opened!\n");
        return BADFILE;
    }

    rewind(fp);
    // process each record
    while(fgets(rec, RECORDSIZE, inputFile) != NULL)
    {
        // get rid of newline characters
        if(*(rec + strlen(rec) - 1) == '\n')
            *(rec + strlen(rec) - 1) = '\0';

        // get pointer to secondcomma
        secondComma = strchr(rec,',');
        secondComma = strchr(secondComma + 1,',');

        // // Get the city and state
        new_length = secondComma - rec;
        strncpy(city_state, rec, new_length);
        *(city_state + new_length) = '\0';

        // begin write procedure
        if(setFilePointer(city_state, fp, 0)) {
            for(i = 0; i < RECS_PER_BUCKET; i++) 
            {
                fread(detect, RECORDSIZE, 1, fp);
                if(strstr(detect, city_state) != NULL) {
                    printf("Duplicate record entry not allowed for %s!\n", city_state);
                    break;
                } 
                if(*detect == ' ') {
                    fseek(fp, -1L * RECORDSIZE, SEEK_CUR);
                    fwrite(rec, RECORDSIZE, 1, fp);
                    break;
                }
            }
            if(i == RECS_PER_BUCKET) 
                printf("Bucket overflow! Record for %s rejected!\n", city_state);
        }
    }
    return 0;
}

// the setFilePointer functino will take in the correct values 
bool setFilePointer(char *city_state, FILE* fp, int add_or_lookup) 
{
    char detect[RECORDSIZE];
    int i;
    rewind(fp);
    long hashval = hash(city_state);

    if (fseek(fp, hashval * BUCKETSIZE, SEEK_SET) != 0)
    {
        printf("Fatal seek error! Abort!\n");
        exit(4);
    }

    fread(detect, RECORDSIZE, 1, fp);
    fseek(fp, -1L * RECORDSIZE, SEEK_CUR); 

    if (*detect == ' ') // available slot
    {
        if(add_or_lookup == 1)
            return false;
        return true;
    } 
    else
        return true;

}

int lookupRecord(FILE *fp)
{
    char line[MAXLINE];
    char detect[RECORDSIZE];
    printf("Enter city, state: ");
    fgets(line, MAXLINE - 1, stdin);

    if(line[strlen(line)-1] == '\n' && strlen(line) == 1) 
        return BLANK;
    *(line + strlen(line) - 1) = '\0';

    char parsed[MAXLINE] = {0};
    int index = 0;
    int i;
    bool lastCharAlpha = false;
    bool city_encountered;
        // - city is encountered when first char of city is found
    int num_commas = 0;

    for(i = 0; i < strlen(line); i++)
    {
        if(!lastCharAlpha && isspace(line[i]))
            continue;
        if(num_commas > 1) {
            printf("Illegal extra token on line!  Try again!\n\n");
            return BADLINE;
        }

        if(isalpha(line[i]))
        {
            if(isspace(parsed[index]))
                index++;
            parsed[index] = toupper(line[i]);
            // printf("%s %c %d\n", parsed, parsed[index],index);
            lastCharAlpha = true;
            index++;
        }
        else if(isspace(line[i])) 
        {
            parsed[index] = line[i];
            lastCharAlpha = false;
        }
        else if(line[i] == ',')
        {
            if(index == 0) {
                printf("Missing city!!  Try again!\n\n");
                return BADLINE;
            }
            else
                parsed[index] = line[i];
            lastCharAlpha = false;
            num_commas++;
            index++;
        }
        else {
            printf("Record not found\n\n");
            return BADLINE;       
        }
    }

    if(parsed[index-1] == ',' || num_commas == 0) {
        printf("Missing state!!  Try again!\n\n");
        return BADLINE;
    }
    else
        parsed[index] = '\0';

    if(setFilePointer(parsed, fp, 1)){
        for(i = 0; i < RECS_PER_BUCKET; i++) 
        {
            fread(detect, RECORDSIZE, 1, fp);
            if(strstr(detect,parsed) != NULL) {
                char *ptr1, *ptr2;
                ptr1 = strtok(detect,",");
                ptr1 = strtok(NULL, ",");
                ptr1 = strtok(NULL, ",");
                ptr2 = strtok(NULL, ",");
                printf("Found record: %s \t\t\t %s  %s\n", parsed, ptr1, ptr2);
                return FOUND;
            }
        }
    }
    printf("Record for %s \t\t\t not found!\n\n", parsed);
    return NOTFOUND;
}

/* Obviously, the hash key is state + city and you should sum the cube of the ASCII values
of the characters making up the city/state before modding by 100 to find
the bucket to put the record.  */
long hash (char *key)
{
    long address = 0;
    for (   ; *key != '\0'; key++)
    {
        address += pow(*key,3) * pow(*key,3) * pow(*key,3);
    }
    return address % BUCKETS;
}

// the menu function will perform input validation for choice desired.
int menu(void) 
{
    int choice;
    char input[50];
    char *token;

    printf("\n1. Add records to database.\n");
    printf("2. Look up a record in the database.\n");
    printf("3. Quit.\n");
    printf("\nEnter selection: ");
    
    fgets(input, sizeof(input) - 1, stdin);
    if(input[0] == '\n') 
        choice = BLANK;
    else
    {
        token = strtok(input, " \t");
        if(strtok(NULL, input) != NULL) {
            printf("Legal entry has one menu selection only!");
            choice = BADLINE;
        }
        else
        {
            choice  = (int) strtol(token, (char **)NULL, 10);
            if(choice > 3 || choice < 1) {
                printf("Illegal menu selection!  Try again!\n");
                choice = BADLINE;
            }
        }
    }
    return choice;
}

/* OUTPUT: 

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 1

Enter filename: /Users/sehun/Documents/26b/hw3/input
Bucket overflow! Record for ASDALL,TEXAS rejected!

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 1

Enter filename: /Users/sehun/Documents/26b/hw3/input
Duplicate record entry not allowed for ALBUQUERQUE,NEW MEXICO!
Duplicate record entry not allowed for RENO,NEVADA!
Duplicate record entry not allowed for LAS VEGAS,NEVADA!
Duplicate record entry not allowed for PHOENIX,ARIZONA!
Duplicate record entry not allowed for SAN FRANCISCO,CALIFORNIA!
Duplicate record entry not allowed for SAN JOSE,CALIFORNIA!
Duplicate record entry not allowed for DEATH VALLEY,CALIFORNIA!
Duplicate record entry not allowed for SEATTLE,WASHINGTON!
Duplicate record entry not allowed for PORTLAND,OREGON!
Duplicate record entry not allowed for MINOT,NORTH DAKOTA!
Duplicate record entry not allowed for PIERRE,SOUTH DAKOTA!
Duplicate record entry not allowed for RAPID CITY,SOUTH DAKOTA!
Duplicate record entry not allowed for MULE SHOE,WEST VIRGINIA!
Duplicate record entry not allowed for PHILADELPHIA,PENNSYLVANIA!
Duplicate record entry not allowed for DALLAS,TEXAS!
Duplicate record entry not allowed for SALLAD,TEXAS!
Duplicate record entry not allowed for DALLSA,TEXAS!
Duplicate record entry not allowed for SALDAL,TEXAS!
Bucket overflow! Record for ASDALL,TEXAS rejected!

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 4
Illegal menu selection!  Try again!

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2 foo
Legal entry has one menu selection only!
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 1

Enter filename:  foobar.foobar
Batch insertion file could not be opened!

Enter filename:

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2
Enter city, state:    foobar,  New  Mexico
Record for FOOBAR,NEW MEXICO             not found!

Enter city, state:     dAllAS        , tExAs
Found record: DALLAS,TEXAS           97  72

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:    alBUquerQUE ,  nEW  MexICO
Legal entry has one menu selection only!
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2
Enter city, state:    alBUquerQUE ,  nEW  MexICO
Found record: ALBUQUERQUE,NEW MEXICO             96  65

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2
Enter city, state:   ,,
Missing city!!  Try again!

Enter city, state: ,
Missing city!!  Try again!

Enter city, state:

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2
Enter city, state: whatever
Missing state!!  Try again!

Enter city, state:

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 3

$
*/