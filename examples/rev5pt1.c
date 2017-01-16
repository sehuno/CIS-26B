// Given a fp a file pointer to binary file (64-byte records), write function calls for each of the following

char table[5][64] = {"One", "Two", "Three", "Four", "Five"};

// A. Move to the beginning of the last record in the file
//  - Each string is of length 64 bytes, with 5 of these strings in a record.

    fseek(fp, -1 * 64, SEEK_END);   // 64 could be replaced by sizeof(RECORD)

// B. Move to the beginning of the record n (1,2,3, ... , n)

    fseek(fp, (n - 1) * 64, SEEK_SET);

// C. Move to the beginning of the first record, then forward one record
//
    //	WRONG
    // fseek(fp, 0, SEEK_SET);
    //	
    //	USE 
    rewind(fp);
    fseek(fp, 1*64, SEEK_CUR);

// D. Move to the beginning of the last record in the file then move backwards two records
//
    fseek(fp, -1 * 64, SEEK_END);
    fseek(fp, -2 * 64, SEEK_CURR);

// E. Replace the nth element by "DONE"

    char word[64];
    fseek(fp, (n-l)*64,SEEK_SET);
    strcpy(word,"DONE");
    fwrite(word, 64, 1, fp);

// F. Change the last letter in the last word to uppercase

    fseek(fp, -1 * 64, SEEK_END);
    fread(word, 64, 1, fp);
    p = word + strlen(word) - 1;
    *p = toupper(*p);
    fseek(fp, -1 * 64, SEEK_CUR);
    fwrite(word, 64, 1, fp);

// G. Append the word "DONE" twice

    fseek(fp, 0, SEEK_END);
    strcpy(word, "DONE");
    fwrite(word, 64, 1, fp);
    fwrite(word, 64, 1, fp)'

    // OR make two records
    // char list [2][64] = { "DONE", "DONE" };
    // fwrite(list, 128, 1, fp);

// H. Calculate the number of records in the file

    fseek(fp, 0, SEEK_END);
    pos = ftell(fp);
    printf("There are %ld records in this file.\n", pos/64);

    
