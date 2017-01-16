/****************************************************************************

   Using qsort and bsearch

****************************************************************************/
#include <stdio.h>
#include <stdlib.h> // qsort, bsearch
#include <string.h>

#define BLOCK 10
#define SENTINEL '~'

typedef struct hardware HARDWARE;
struct hardware
{
    char partname[20];
    int quantity;
};

//int main(argcm char **argv)
int main(void)
{
    FILE *open_file(char *filename);
    HARDWARE *read_file(FILE *parts, long *numparts);
    //void print_sorted_output(HARDWARE *inventory);
    void print_inventory(HARDWARE *inventory);
    int compare(const void *part1, const void *part2);
    int compareQty(const void *part1, const void *part2);
    void find_keys(HARDWARE *inventory, long numparts);
    void find_qtys(HARDWARE *inventory, long numparts);

    FILE *parts;
    HARDWARE *inventory;
    long numparts;

    //parts = open_file(argv[1]);
    parts = open_file("in.txt");
    inventory = read_file(parts, &numparts);
    fclose(parts);
    printf("\nUNSORTED: \n");
    print_inventory(inventory);
    qsort(inventory, numparts, sizeof(HARDWARE), compare);
    printf("\nSORTED BY PARTNAME: \n");
    print_inventory(inventory);
    printf("\n\n");
    find_keys(inventory, numparts); // calls bsearch

    qsort(inventory, numparts, sizeof(HARDWARE), compareQty);
    printf("\nSORTED BY QUANTITY: \n");
    print_inventory(inventory);
    find_qtys(inventory, numparts); // calls bsearch

    return 0;
}

/*************************************************************
  Open input file
*/
FILE *open_file(char *filename)
{
    FILE *parts;

    if ((parts = fopen(filename, "r")) == NULL)
    {
        printf("Cannot open file: %s.\n", filename);
        exit(1);
    }
    return parts;
}

/*************************************************************
  Read input file into array
  Dynamically increase size of array with realloc.
*/
HARDWARE *read_file(FILE *parts, long *numparts)
{
    HARDWARE *inventory, *mover;
    char line[80], *partname, *pqty;
    long numlines = 0;

    if ((inventory = (HARDWARE *)
                      malloc(BLOCK * sizeof (HARDWARE))) == NULL)
    {
        printf("Fatal malloc error!\n");
        exit(2);
    }
    memset(inventory, 0, BLOCK * sizeof(HARDWARE));

    mover = inventory;
    while (fgets(line, 80, parts))
    {
        numlines++;
        partname = strtok(line, ":");
        pqty     = strtok(NULL, "\040");
        mover->quantity = (int) strtol(pqty, NULL, 10);
        strcpy(mover->partname, partname);
        if (numlines % BLOCK == 0)
        {
            if ((inventory = (HARDWARE *)
                 realloc(inventory,
                        (numlines + BLOCK) * sizeof (HARDWARE))) == NULL)
            {
                printf("Fatal realloc error!\n");
                exit(3);
            }
            mover = inventory + numlines; // MUST update mover
            memset(mover, 0, BLOCK * sizeof (HARDWARE));
        }
        // mover++; 
        else  // to avoid adding empty elements
            mover++;
    }
    *mover->partname = SENTINEL;
    *numparts = numlines;
    return inventory;
}

/*************************************************************
  Print array
  Do not print the sentinel record
*/
 void print_inventory(HARDWARE *inventory)
 {
     HARDWARE *mover;

     for (mover = inventory; *mover->partname != SENTINEL; mover++)
     {
         //if (*mover->partname != '\0') // there are no empty elements
         printf("%-20s%-5d\n", mover->partname, mover->quantity);
     }
     printf("\n");
     return;
 }

/*************************************************************
  Used by qsort and bsearch to compare two keys,
  i.e., the partname component. Use memcpy to
  put parameters into HARDWARE structs
*/
int compare(const void *part1, const void *part2)
{
    /*
    HARDWARE p1 = part1, p2;

    memcpy(&p1, part1, sizeof (HARDWARE));
    memcpy(&p2, part2, sizeof (HARDWARE));
    */

    const HARDWARE *p1 = part1, *p2 = part2;
    int cmpres = strcmp(p1->partname, p2->partname);

    if (cmpres > 0) return 1;
    else if (cmpres < 0) return -1;
    else return 0;

    
    // return strcmp(p1->partname, p2->partname);
}

/*************************************************************
  Used by qsort and bsearch to compare two keys,
  i.e., the part quantity component. 
*/
int compareQty(const void *part1, const void *part2)
{
    const HARDWARE *p1 = part1, *p2 = part2;

    if (p1->quantity > p2->quantity)
        return 1;
    else if (p1->quantity < p2->quantity)
        return -1;
    else
        return 0;
    //return p1->quantity - p2->quantity;
}

/*************************************************************
  Get user tokens from terminal
  Find in array with bsearch
*/
void find_keys(HARDWARE *inventory, long numparts)
{
    void format(char *key);

    HARDWARE *found, temp;
    char line[80];

    while (printf("Enter key: "), gets(line),
           format(line), strcmp(line, "QUIT") != 0)
    {
        if (*line == '\0') continue; // empty response
        memset(&temp, 0, sizeof(HARDWARE));
        strcpy(temp.partname, line);
        found = (HARDWARE *)bsearch(&temp,
                                    inventory,
                                    numparts,
                                    sizeof (HARDWARE),
                                    compare);
        if (!found) printf("Could not find key: %s\n", line);
        else printf("Found record: %s %d\n", found->partname, found->quantity);
    }
    return;
}

/*************************************************************
  Get user tokens from terminal
  Find in array with bsearch
*/
void find_qtys(HARDWARE *inventory, long numparts)
{
    void format(char *key);

    HARDWARE *found, temp;
    char line[80];
    int num;

    while (printf("Enter key: "), gets(line), format(line), 
           sscanf(line, "%d", &num), strcmp(line, "QUIT") != 0)
    {
        if (*line == '\0') continue; // empty response
        memset(&temp, 0, sizeof(HARDWARE));
        temp.quantity = num;
        found = (HARDWARE *)bsearch(&temp,
                                    inventory,
                                    numparts,
                                    sizeof (HARDWARE),
                                    compareQty);
        if (!found) printf("Could not find key: %d\n", num);
        else printf("Found record: %s %d\n", found->partname, found->quantity);
    }
    return;
}

/*************************************************************
  Uppercases all characters in key
  Trims leading and trailing space.
  Puts one space between tokens in "key"
*/
void format(char *key)
{
    char line[80], *token, *keyptr = key;

    strcpy(line, "");
    for ( ; token = strtok(keyptr, "\040"); keyptr = NULL)
    {
        strcat(line, token);
        strcat(line, "\040");
    }
    line[strlen(line) - 1] = '\0'; // overwrite space
    strcpy(key, line);
    while (*key != '\0')
    {
        *key = toupper(*key);
        key++;
    }
    return;
}

