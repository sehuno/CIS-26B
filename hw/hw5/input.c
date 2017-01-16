#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCITIES 100
#define MAXLINE    80

struct weather
{
    char *statecity;
    int   tempsum;
    int   count;
};


int main(int argc, char **argv)
{
    struct weather highTemps[MAXCITIES] = {{"", 0, 0}};
    FILE *fin, *fout;
    void checkArgs(int argc,char *infile,char *outfile,FILE **fin,FILE **fout);
    int readIntoWeatherStructs(struct weather *highTemps, FILE *fin), count;
    void writeAveragesToOutput(struct weather *hightemps, int count, FILE *fin);
    
    checkArgs(argc, argv[1], argv[2], &fin, &fout);
    count = readIntoWeatherStructs(highTemps, fin);
    writeAveragesToOutput(highTemps, count, fout);
}




void checkArgs(int argc, char *infile, char *outfile, FILE **fin, FILE **fout)
{
    if (argc != 3)
    {
        printf("Wrong number of arguments on command line!\n");
        exit(1);
    }

    if ((*fin = fopen(infile, "r")) == NULL)
    {
        perror("Cannot open input file");
        exit(1);
    }

    if ((*fout = fopen(outfile, "w")) == NULL)
    {
        perror("Cannot open output file");
        exit(1);
    }
} 


     
int readIntoWeatherStructs(struct weather *highTemps, FILE *fin)
{
    int count = 0, first = 1, highTemp;
    char city[MAXLINE], line[MAXLINE];
   
    while (fgets(line, MAXLINE, fin))
    {
         sscanf(line, "%s %d", city, &highTemp);
         if (strcmp(city, highTemps[count].statecity) != 0)
         {
              if (first) first = 0;
              else count++;
              highTemps[count].tempsum = highTemp; 
              highTemps[count].count = 1;

              if ((highTemps[count].statecity = 
                   (char *) malloc(strlen(city) + 1)) == NULL)
              {
                  perror("Malloc error!");
                  exit(1);
              }
              strcpy(highTemps[count].statecity, city);                
         }
         else
         {
              highTemps[count].tempsum += highTemp;
              highTemps[count].count++;
         } 
    }
    return count;
}




void writeAveragesToOutput(struct weather *highTemps, int count, FILE *fout)
{
     int i;

     for (i = 0; i <= count; i++) 
        fprintf(fout, "%s %-5.1f\n", highTemps[i].statecity,
                 (float) highTemps[i].tempsum/highTemps[i].count);
}