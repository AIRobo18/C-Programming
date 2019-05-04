/**
 * This implements the LRU page-replacement strategy.
 */

#include "replace.h"

// the page frame list
int *pageTableLFU;
int numOfpagesLFU;
int *countPageTableLFU;

// the number of elements in the page list
int nextVictimIndexLFU = 0;

// the last page insertLFUed
int lastReferencedLFU = -1;

// statistics
int numOfFaultsLFU = 0;

// this is the sequencxe of pages to serve
int *referenceStringLFU;
int refStringLengthLFU;

void displayLFU(void);
void insertLFU(int, int);
void updatePageTableLFU(int, int);
int searchLFU(int);

/*
 * insertLFU pages from a reference string into a page table and measure
 * the page fault rate
 */
int testLFU(int n, int *refString, int refStrLen)
{
	numOfpagesLFU = n;
	referenceStringLFU = refString;
	refStringLengthLFU = refStrLen;

	pageTableLFU = calloc(numOfpagesLFU, sizeof(int));
	countPageTableLFU = calloc(numOfpagesLFU, sizeof(int));

	// we use an impossible page reference of -1 as an initial value
	memset(pageTableLFU, -1, numOfpagesLFU * sizeof(int));
	nextVictimIndexLFU = 0;

	#if DEBUGLEVEL > 2
	   printf("      ");
	#endif

	#if DEBUGLEVEL > 0
	   displayLFU();
	#endif

	// output a message when insertLFUing a page
	int i;
   for (i = 0; i < refStringLengthLFU; i++)
	{
		insertLFU(referenceStringLFU[i], i);

		#if DEBUGLEVEL > 2
				printf("{%3d}", referenceStringLFU[i]);
		#endif

		#if DEBUGLEVEL > 0
		      displayLFU();
		#endif

	}

	#if DEBUGLEVEL > 2
	   printf("      ");
	#endif

	#if DEBUGLEVEL > 0
	   displayLFU();
	#endif

	return numOfFaultsLFU;
}

/*
 *	try to insertLFU a page into the page table
 */
void insertLFU(int pageNumber, int index)
{
	int searchLFUVal = searchLFU(pageNumber);

	// if we didn't find it, replace the LRU page
	if (searchLFUVal == -1)
	{
		numOfFaultsLFU++;
		// pageTableLFU[nextVictimIndexLFU] = pageNumber;
     	// nextVictimIndexLFU = (nextVictimIndexLFU + 1) % numOfpagesLFU;
		updatePageTableLFU(pageNumber, index);

		#if DEBUGLEVEL > 2
		      printf("*");
		#endif
	}
	else
    {

		#if DEBUGLEVEL > 2
		      printf(" ");
		#endif

		countPageTableLFU[searchLFUVal]++;

     //  	if (pageNumber != lastReferencedLFU)
	    // {
	    //     /**
	    //      * We only update the page table if the page being
	    //      * referenced was not the last one referenced.
	    //      * If it was the last page referenced, leave the
	    //      * page table as is.
	    //      */
	    //     // updatePageTableLFU(searchLFUVal);
	    //     lastReferencedLFU = pageNumber;
	    // }
    }
}

void updatePageTableLFU(int pageNumber, int index)
{
	int leastUsedIndex = 0;
	for (int i = 1; i < numOfpagesLFU; i++) {
		if (countPageTableLFU[i] < countPageTableLFU[leastUsedIndex]) {
			leastUsedIndex = i;
		}
	}

	pageTableLFU[leastUsedIndex] = pageNumber;
	countPageTableLFU[leastUsedIndex] = 1;

	// int mostRecetnlyReferencedPage = pageTableLFU[searchLFUVal];

	// if the page to be updated is already the next page to be the victim
	// just increment nextVictimIndexLFU -- jump over the body of the following "if"

	// otherwise shift the page references, so the oldest is always the next victim
	// it's like the top of the stack; always pointing to the latest used
	// if (mostRecetnlyReferencedPage != pageTableLFU[nextVictimIndexLFU])
	// {
	// 	// now shift all elements left making room at the "top of the stack"
  //     // for the referenced page
	//
	// 	int rightIndex = searchLFUVal;
	// 	int leftIndex = (rightIndex == 0) ? numOfpagesLFU - 1 : searchLFUVal - 1;
	//
	// 	while (rightIndex != nextVictimIndexLFU )
	// 	{
	// 		pageTableLFU[rightIndex] = pageTableLFU[leftIndex];
	// 		rightIndex = leftIndex;
	//
	// 		leftIndex = (leftIndex == 0) ? numOfpagesLFU - 1 : leftIndex - 1;
	// 	}
	// 	pageTableLFU[rightIndex] = mostRecetnlyReferencedPage;
	// }

   // at this moment, nextVictimIndexLFU is pointing to the most recenty referenced page
   // the following will make that page the furthest from being a victim (i.e. it will
   // be the top of the stack

	// nextVictimIndexLFU = (nextVictimIndexLFU + 1) % numOfpagesLFU;
}

/**
 * Searches for page pageNumber in the page frame list
 * returns non-negative integer if pageNumber was found
 * returns -1 if pageNumber was not found
 */
int searchLFU(int pageNumber)
{
	for (int i = 0; i < numOfpagesLFU; i++)
		if (pageNumber == pageTableLFU[i])
			return i;
	return -1;
}

void displayLFU()
{
	for (int i = 0; i < numOfpagesLFU; i++)
   {
#if DEBUGLEVEL > 1
		printf("%s", ((i == nextVictimIndexLFU) ? " ->" : "   "));
#endif
		printf("[%3d]", pageTableLFU[i]);
   }
   printf("\n");
}
