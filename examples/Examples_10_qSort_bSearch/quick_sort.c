/***********************************************
	Test driver for sorting. 
	Note that the minimum size is set to 2.
	Be sure to test with a minSize that tests both quick
	and insertion sorts.
*/
#include <stdio.h>
#define MAX_ARY_SIZE 20

void quickSort       (int sortData[ ], int left, int right);
void quickInsertion	 (int sortData[ ], int first, int last); 
void medianLeft		 (int sortData[ ], int left, int right); 
	
int main (void) 
{
	int i ;
	int	ary[ MAX_ARY_SIZE ] = { 89, 72, 3,  15, 21, 
							    57, 61, 44, 19, 98, 
							    5,  77, 39, 59, 61, 
                                88, 79, 2,  15, 24 };

	printf("Unsorted array: ");
	for (i = 0; i < MAX_ARY_SIZE; i++)
		printf("%3d", ary[ i ]);
		
	quickSort (ary, 0, MAX_ARY_SIZE - 1);

	printf("\nSorted array:   ");
	for (i = 0; i < MAX_ARY_SIZE; i++)
		printf("%3d", ary[ i ]);
	printf("\n");
	return 0;
}

/*	====================================================
	Array, sortData[left..right] sorted using recursion.
	   . sortData is an array of data to be sorted
	   . left identifies first element of sortData 
	   . right identifies last element of sortData 	   
*/
void quickSort (int sortData[ ], int left, int right)
{
#define MIN_SIZE 3          // set to 3 for testing

    int sortLeft, sortRight, pivot, hold;


	if ((right - left) > MIN_SIZE)
	{
	   medianLeft (sortData, left, right);
	   pivot     = sortData [left];
	   sortLeft  = left + 1;
	   sortRight = right;
	   while (sortLeft <= sortRight)
	   {
	      // Find key on left that belongs on right 
	      while (sortData [sortLeft] < pivot) 
	         sortLeft = sortLeft + 1;
	      // Find key on right that belongs on left 
	      while (sortData[sortRight] >= pivot)
	         sortRight = sortRight - 1;
	      if (sortLeft <= sortRight)
	      {
	         hold                = sortData[sortLeft];
	         sortData[sortLeft]  = sortData[sortRight];
	         sortData[sortRight] = hold;
	         sortLeft            = sortLeft  + 1;
	         sortRight           = sortRight - 1;
	      }
	   }
	   // Prepare for next pass 
	   sortData [left]         = sortData [sortLeft - 1];
	   sortData [sortLeft - 1] = pivot;
	   if (left < sortRight)
	       quickSort (sortData, left, sortRight - 1);
	   if (sortLeft < right)
	       quickSort (sortData, sortLeft, right);
	}  
	else
	  quickInsertion (sortData, left, right);
    return;
}	

/*	======================================================
	Sort data[] using insertion sort. data is 
	divided into sorted and unsorted lists. With each 
	pass, the first element in unsorted list is inserted 
	into the sorted list. This is a special version of the 
	insertion sort modified for use with quick sort.
	   . data must contain at least one element
	   . first is index to first element in data
	   . last is index to last element in data	  
*/
void quickInsertion (int data[], int first, int last)
{
	int hold, walker, current;

	for (current = first + 1; current <= last; current++)
	{
	    hold   = data[current];
	    walker = current - 1;
	    while (walker >= first && hold < data[walker])
	    {
	        data[walker + 1] = data[walker];
	        walker--;
	    } 
	    data[walker + 1] = hold;
	} 
	return;
}	

/*	=======================================================
	Find the median value of an array, 
	sortData[left..right], and place it in the 
	location sortData[left].
	   . sortData is array of at least three elements
	   . left and right are boundaries of array
	   . median value placed at sortData[left]
*/
void medianLeft (int sortData[], int left, int right)
{
	int mid, hold;

	// Rearrange sortData so median is middle location 
	mid = (left + right) / 2;
	if (sortData[left] > sortData[mid])
	{
	    hold            = sortData[left];
	    sortData[left]  = sortData[mid];
	    sortData[mid]   = hold;
	} 
	if (sortData[left] > sortData[right])
	{
	    hold            = sortData[left];
	    sortData[left]  = sortData[right];
	    sortData[right] = hold;
	} 
	if (sortData[mid]  > sortData[right])
	{
	    hold            = sortData[mid];
	    sortData[mid]   = sortData[right];
	    sortData[right] = hold;
	}
	   
	// Median is in middle. Exchange with left 
	hold           = sortData[left];
	sortData[left] = sortData[mid];
	sortData[mid]  = hold;

	return;
}	

