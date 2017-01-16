#include <stdio.h>

int main() 
{
	// READING AND WRITING A DOUBLE
	//	- Writing must can use %f
	fp = fopen("num.txt", "w");	//	- Writing must can use %f
	fprintf(fp, "%f", x);	
	fclose(fp);

	fp = fopen("num.txt", "r"); 	
	fscanf(fp, "%lf", &y); 		// 	- Reading must use %lf
	fclose(fp);

	

	return 0;

}