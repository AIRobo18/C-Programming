/**
 * This implements the LRU page-replacement strategy.
 */

#include "replace.h"

// the page frame list
int *pageTableOPT;
int numOfpagesOPT;

// the number of elements in the page list
int nextVictimIndexOPT = 0;

// the last page insertOPTed
int lastReferencedOPT = -1;

// statistics
int numOfFaultsOPT = 0;

// this is the sequencxe of pages to serve
int *referenceStringOPT;
int refStringLengthOPT;

void displayOPT(void);
void insertOPT(int, int);
void updatePageTableOPT(int, int);
int searchOPT(int);

/*
 * insertOPT pages from a reference string into a page table and measure
 * the page fault rate
 */
int testOPT(int n, int *refString, int refStrLen)
{
	numOfpagesOPT = n;
	referenceStringOPT = refString;
	refStringLengthOPT = refStrLen;

	pageTableOPT = calloc(numOfpagesOPT, sizeof(int));

	// we use an impossible page reference of -1 as an initial value
	memset(pageTableOPT, -1, numOfpagesOPT * sizeof(int));
	nextVictimIndexOPT = 0;

	#if DEBUGLEVEL > 2
	   printf("      ");
	#endif

	#if DEBUGLEVEL > 0
	   displayOPT();
	#endif

	// output a message when insertOPTing a page
	int i;
   for (i = 0; i < refStringLengthOPT; i++)
	{
		insertOPT(referenceStringOPT[i], i);

		#if DEBUGLEVEL > 2
				printf("{%3d}", referenceStringOPT[i]);
		#endif

		#if DEBUGLEVEL > 0
		      displayOPT();
		#endif

	}

	#if DEBUGLEVEL > 2
	   printf("      ");
	#endif

	#if DEBUGLEVEL > 0
	   displayOPT();
	#endif

	return numOfFaultsOPT;
}

/*
 *	try to insertOPT a page into the page table
 */
void insertOPT(int pageNumber, int index)
{
	int searchOPTVal = searchOPT(pageNumber);

	// if we didn't find it, replace the LRU page
	if (searchOPTVal == -1)
	{
		numOfFaultsOPT++;
		// pageTableOPT[nextVictimIndexOPT] = pageNumber;
     	// nextVictimIndexOPT = (nextVictimIndexOPT + 1) % numOfpagesOPT;
		updatePageTableOPT(pageNumber, index);

		#if DEBUGLEVEL > 2
		      printf("*");
		#endif
	}
	else
    {

		#if DEBUGLEVEL > 2
		      printf(" ");
		#endif

      	if (pageNumber != lastReferencedOPT)
	    {
	        /**
	         * We only update the page table if the page being
	         * referenced was not the last one referenced.
	         * If it was the last page referenced, leave the
	         * page table as is.
	         */
	        // updatePageTableOPT(searchOPTVal);
	        lastReferencedOPT = pageNumber;
	    }
    }
}

void updatePageTableOPT(int pageNumber, int index)
{
	for (int i = 0; i < numOfpagesOPT; i++) {
		if (pageTableOPT[i] == -1) {
			pageTableOPT[i] = pageNumber;
			return;
		}
	}

	int count = 0;
	int *checkTable = calloc(numOfpagesOPT, sizeof(int));

	for (int i = index; i < refStringLengthOPT; i++) {
		for (int j = 0; j < numOfpagesOPT; j++) {
			if (count >= (numOfpagesOPT - 1)) {
				break;
			}
			else if (pageTableOPT[j] == referenceStringOPT[i]) {
				checkTable[j] = 1;
				count++;
			}
		}
	}
	count = 0;

	for (int i = 0; i < numOfpagesOPT; i++) {
		// printf("%d\n", checkTable[i]);
		if (checkTable[i] != 1) {
			// printf("We in\n");
			pageTableOPT[i] = pageNumber;
		}
	}
	memset(checkTable, 0, numOfpagesOPT * sizeof(int));

	// int mostRecetnlyReferencedPage = pageTableOPT[searchOPTVal];

	// if the page to be updated is already the next page to be the victim
	// just increment nextVictimIndexOPT -- jump over the body of the following "if"

	// otherwise shift the page references, so the oldest is always the next victim
	// it's like the top of the stack; always pointing to the latest used
	// if (mostRecetnlyReferencedPage != pageTableOPT[nextVictimIndexOPT])
	// {
	// 	// now shift all elements left making room at the "top of the stack"
  //     // for the referenced page
	//
	// 	int rightIndex = searchOPTVal;
	// 	int leftIndex = (rightIndex == 0) ? numOfpagesOPT - 1 : searchOPTVal - 1;
	//
	// 	while (rightIndex != nextVictimIndexOPT )
	// 	{
	// 		pageTableOPT[rightIndex] = pageTableOPT[leftIndex];
	// 		rightIndex = leftIndex;
	//
	// 		leftIndex = (leftIndex == 0) ? numOfpagesOPT - 1 : leftIndex - 1;
	// 	}
	// 	pageTableOPT[rightIndex] = mostRecetnlyReferencedPage;
	// }

   // at this moment, nextVictimIndexOPT is pointing to the most recenty referenced page
   // the following will make that page the furthest from being a victim (i.e. it will
   // be the top of the stack

	// nextVictimIndexOPT = (nextVictimIndexOPT + 1) % numOfpagesOPT;
}

/**
 * SearchOPTes for page pageNumber in the page frame list
 * returns non-negative integer if pageNumber was found
 * returns -1 if pageNumber was not found
 */
int searchOPT(int pageNumber)
{
	for (int i = 0; i < numOfpagesOPT; i++)
		if (pageNumber == pageTableOPT[i])
			return i;
	return -1;
}

void displayOPT()
{
	for (int i = 0; i < numOfpagesOPT; i++)
   {
#if DEBUGLEVEL > 1
		printf("%s", ((i == nextVictimIndexOPT) ? " ->" : "   "));
#endif
		printf("[%3d]", pageTableOPT[i]);
   }
   printf("\n");
}
