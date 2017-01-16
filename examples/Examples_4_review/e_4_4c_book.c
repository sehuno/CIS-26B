/***********************************************************************
    Examples: 4.4 Using
    strspn to search for the first character that IS NOT in a given set
    and
    strcspn to search for the first character that IS in a given set
/***********************************************************************/

#include <stdio.h>
#include <string.h>

int main (void)
{
    char sentence[] = "Hello, I am John!";
    char nonsense[] = "~*%#";
    char letters[]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                       "abcdefghijklmnopqrstuvwxyz";
    int n;

    printf( "sentence: %s\n", sentence);
    printf( "nonsense: %s\n", nonsense);
    printf( "letters: %s\n\n", letters);

    n = strcspn(sentence, letters); // 0
    printf("%d chars skipped over until a letter was found.\n", n);

    n = strspn(sentence, letters); // 5
    printf("%d chars skipped over until a non-lettr was found.\n", n);

    n = strcspn(sentence, nonsense); // 17
    printf("%d chars skipped over until a nonsense character was found.\n", n);
    return 0;
}

