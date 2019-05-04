/*
 *  replace.c
 *
 *  Created by AJ Bieszczad on 4/9/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#include "replace.h"
#include <time.h>
#define NUM_OF_TESTS 3
#define NUM_OF_RUNS 1000

int main(int argc, char *argv[])
{
	int sizeOfRefString;
	if (argc < 4)
		oops("Usage:\n   replace <num of frames> <ref string length> <value range>\n   replace <number of frames> -s <reference string> \n", 1);

	int numOfFrames = atoi(argv[1]);

	if (argv[2][0] == '-')
		sizeOfRefString = argc - 3; // prog name + num of frames + '-s'
	else
		sizeOfRefString = atoi(argv[2]);

	int *referenceString = calloc(sizeOfRefString, sizeof(int));

	if (argv[2][0] == '-')
		for (int i = 3; i < argc; i++) {
			referenceString[i - 3] = atoi(argv[i]);
		}
	else {
		int range = atoi(argv[3]);

		int average[NUM_OF_TESTS] = {0, 0, 0};

		// create a random page reference sequence from [0, range-1]
		for (int i = 0; i < NUM_OF_RUNS; i++) {
			srand((unsigned int)time(NULL));
			for (int i = 0; i < sizeOfRefString; i++)
				referenceString[i] = rand() % range;

			int numOfFaultsLRU = testLRU(numOfFrames, referenceString, sizeOfRefString);
			int numOfFaultsOPT = testOPT(numOfFrames, referenceString, sizeOfRefString);
			int numOfFaultsLFU = testLFU(numOfFrames, referenceString, sizeOfRefString);

			average[0] += numOfFaultsLRU;
			average[1] += numOfFaultsOPT;
			average[2] += numOfFaultsLFU;
		}

		average[0] = average[0] / NUM_OF_RUNS;
		average[1] = average[1] / NUM_OF_RUNS;
		average[2] = average[2] / NUM_OF_RUNS;

		printf("\nAverage number of page faults using LRU: %d\n", average[0]);
		printf("\nAverage number of page faults using OPT: %d\n", average[1]);
		printf("\nAverage number of page faults using LFU: %d\n", average[2]);

		free(referenceString);

		exit(0);
	}

	printf("REFERENCE STRING:\n{");
	for (int i = 0; i < sizeOfRefString; i++)
		printf("%d ", referenceString[i]);
	printf("}\n");

	// use the LRU replacement policy to count page faults for the sequence
	int numOfFaultsLRU = testLRU(numOfFrames, referenceString, sizeOfRefString);
	int numOfFaultsOPT = testOPT(numOfFrames, referenceString, sizeOfRefString);
	int numOfFaultsLFU = testLFU(numOfFrames, referenceString, sizeOfRefString);
	printf("\nNumber of page faults using LRU: %d\n", numOfFaultsLRU);
	printf("\nNumber of page faults using OPT: %d\n", numOfFaultsOPT);
	printf("\nNumber of page faults using LFU: %d\n", numOfFaultsLFU);

	free(referenceString);
}
