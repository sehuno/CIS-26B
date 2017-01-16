/*********************************************************
    Examples: 4.11 Case study of string handling:
    The Word Counter Program: the program counts the
    frequency of words in a file. Words are defined as
    any combination of letters, digits, hyphens, or periods.
    However, a word cannot be ALL hyphens. Also, a period at
    the end of a word will be considered an end-of-sentence
    marker and NOT as part of a word.
/*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // to be added

#define DUPLICATE 1
#define NEW_WORDNODE 0
#define DUMMY_TRAILER '\177'
#define PERIOD '.'
#define DELIMS "\001\
\002\003\004\005\006\007\010\011\012\013\014\015\016\017\020\
\021\022\023\024\025\026\027\030\031\032\033\034\035\036\
\037\040!\"#$%&()|'*+,?/:;<=>@[\092]^_{}~\177"

typedef struct node WORDNODE;
struct node
{
    char *word;
    int count;
    WORDNODE *next;
};

int main (void)
{
    WORDNODE *init_list(void);
    WORDNODE *find(WORDNODE *list, char *word);
    void traverse(WORDNODE *list);
    char *get_filename(void);
    FILE *open_file(char *filename);
    void read_file_into_list(WORDNODE *list, FILE *wordfile);

    WORDNODE *list;
    char *filename;
    FILE *wordfile;

    list = init_list();
    filename = get_filename();
    wordfile = open_file(filename);
    read_file_into_list(list, wordfile);
    fclose(wordfile);
    traverse(list);

    return 0;
}
/**************************************************************
  Get lines from input file. Fetch all word tokens from eac line.
  Put words and their frequency count into a linked list with
  nodes in ASCII order.
*/
void read_file_into_list(WORDNODE *list, FILE *wordfile)
{
    void insert(WORDNODE *list, char *word);

    char line[1024], *word, *mover, *ptr;

    while (fgets(line, 1024, wordfile))
    {
        for (ptr = line; word = strtok(ptr, DELIMS); ptr = NULL)
        {
            if (strspn(word, "-") == strlen(word)) continue;
            if (word[strlen(word) - 1] == PERIOD )
            {
                word[strlen(word) - 1] = '\0';
            }
            for (mover = word; *mover != '\0'; mover++)
            {
                *mover = tolower(*mover);
            }
            insert(list, word);
        }
    }
}
/**************************************************************
  Move across the word list. Print the words and their
  frequency counts in ASCII order to file freq.txt
*/
void traverse(WORDNODE *list)
{
    FILE *freq_file;
    if ((freq_file = fopen("freq.txt", "w")) == NULL)
    {
        printf("Could not open output file!\n");
        exit(4);
    }
    list = list->next;
    while (*list->word != DUMMY_TRAILER)
    {
        fprintf(freq_file, "%-20s %-5d\n", list->word, list->count);
        list = list->next;
    }
    fclose(freq_file);
    return;
}
/**************************************************************
  Insert a word into an ordered linked list. If the word is
  already in the list, increase the frequency count by one
  and do NOT insert a new node.
*/

void insert(WORDNODE *list, char *word)
{
    WORDNODE *curr = list->next;
    WORDNODE *prev = list;
    WORDNODE *pnew;

    while (strcmp(word, curr->word) > 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (strcmp(word, curr->word) == 0)
    {
        curr->count++;
    }
    else // add a new node
    {
        if ((pnew = (WORDNODE *)malloc(sizeof (WORDNODE))) == NULL)
        {
            printf("Fatal malloc error in insert!\n");
            exit(3);
        }
        if ((pnew->word = (char *)malloc(strlen(word) + 1)) == NULL)
        {
            printf("Fatal malloc error in insert");
            exit(3);
        }
        strcpy(pnew->word, word);
        pnew->next = curr;
        pnew->count = 1;
        prev->next = pnew;
    }
    return;
}
/**************************************************************
  Obtain input filename from user. User's entered filename has
  white space removed and all chars are lowecased.
*/
char *get_filename(void)
{
    static char filename[512];  // see return
    char *slow, *fast;

    printf("Enter a file name: ");
    gets(filename);
    // remove whitespace and lowercase the name
    slow = fast = filename;
    while (*fast)
    {
        if (!isspace(*fast)) *slow++ = tolower(*fast);
        fast++;
    }
    *slow = '\0';
    return filename;
}
/**************************************************************
  Open user-specified input file. Abort if unseccessful.
  Pass FILE pointer back if open is successful.
*/
FILE *open_file(char *filename)
{
    FILE *wordfile;

    if ((wordfile = fopen(filename, "r")) == NULL)
    {

        printf("Fatal error opening input file!\n");
        exit(2);
    }
    return wordfile;
}
/**************************************************************
  Initialize list with dummy header and trailer node.
  Header node has an empty string.
  Trailer node is "\177"
*/
WORDNODE *init_list(void)
{
    WORDNODE *list;

    if ((list = (WORDNODE *)malloc(sizeof (WORDNODE))) == NULL)
    {
        printf("Fatal malloc error in init_list!\n");
        exit(1);
    }
    if ((list->word = (char *)malloc(1)) == NULL)
    {
        printf("Fatal malloc error in init_list!\n");
        exit(1);
    }
    if ((list->next = (WORDNODE *)malloc(sizeof (WORDNODE))) == NULL)
    {
        printf("Fatal malloc error in init_list!\n");
        exit(1);
    }
    if ((list->next->word = (char *)malloc(2)) == NULL)
    {
        printf("Fatal malloc error in init_list!\n");
        exit(1);
    }
    *list->next->word = DUMMY_TRAILER;
    list->next->word[1] = '\0';
    list->next->next = NULL;

    return list;
}
