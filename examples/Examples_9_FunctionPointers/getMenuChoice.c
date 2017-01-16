// Why not an array of pointers to strings????
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#define TEMPSTR 20

int myGets(FILE* fp, char str[], int maxSize);
int getMenuChoice(int n, ...);

int main(void)
{

        printf("You chose %d\n", getMenuChoice(3, "Option 1", "Option 2", "Option 3"));
        printf("You chose %d\n", getMenuChoice(2, "Option 1", "Option 2"));
        return 0;
}

int getMenuChoice(int n, ...)
{
	int i, choice, success;
	char temp[TEMPSTR], *endp;
	va_list argp;
	va_start(argp, n);

	printf(	"\nMenu Options\n");
	for(i = 1; i <= n ; i++){
		printf(	"%d) %s\n", i, (char*)va_arg(argp, char*));
	}
	printf("-----------------------\n");
	do{
		printf("Enter choice: ");
		success = 1;
		myGets(stdin, temp, TEMPSTR);
		choice = (int) strtol(temp, &endp, 10);
		if(*endp != 0 || choice < 1 || choice > n){
			printf("Invalid Option!\n");
			success = 0;
		}
	}while(!success);

	va_end(argp);

	return choice;
}
int myGets(FILE* fp, char str[], int maxSize)
{
	int len;
	char ch;

	if(fgets(str, maxSize, fp)== NULL) return EOF;
	len=strlen(str);
	if(str[len-1]=='\n' || str[len-1] == '\r'){
		str[len-1]='\0';
		len--;
	}
	else while((ch=fgetc(fp)) != '\n' /*&& ch != '\r'*/);//flush

	return len;
}
