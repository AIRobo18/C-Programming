/*
	Robert Aroutiounian
	Lab 8 Task 3
	3/16/17
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#define MEM_SIZE 500
#define FRAME_SIZE 10
#define PID 1000
#define PAGE 10
#define OFFSET 50

struct inv_table table;
struct inv_table_page table_page;

// struct inv_table_page {
// 	int pid;
// 	int page;
// 	int time_created;
// };

// struct inv_table {
// 	int frame_size;
// 	int mem_size;
// 	int number_of_pages; // equal to (mem_size / frame_size)
// 	struct inv_table_page *pages;
// };

void initInverted(struct inv_table *invTable, int memSize, int frameSize);
/*
* allocates and initializes the table for the given sizes of the memory and frame
* to ensure that the library is thread-safe, the table should be a struct that
* includes metadata such as page size and the number of pages along the translation
* table (that can be a 2-dimensional array, or a one-dimensional array of structs)
*/

int translate(struct inv_table invTable, int pid, int page, int offset);
/*
* translates a logical address <pid, page, offset> into a physical address
* if the address is invlid it returns -1
* if there is no entry for the pid and the page number in the table, it has to be added
* if there is no room in the table for the new entry, then the oldest entry has to be removed
*/

void releaseInverted(struct inv_table *invTable);
/*
* releases the inverted table and sets the reference to NULL
*/

void initInverted(struct inv_table *invTable, int memSize, int frameSize) {
	// printf("INSDE INITINVERTED\n");
	time_t t;

	invTable->frame_size = frameSize;
	invTable->mem_size = memSize;
	invTable->number_of_pages = (invTable->mem_size / invTable->frame_size);
	invTable->pages = malloc(sizeof(struct inv_table_page)*invTable->number_of_pages);

	// printf("Number of pages: %d\n", invTable->number_of_pages);

	for (int i = 0; i < invTable->number_of_pages; ++i)
	{
		t = time(NULL);

		invTable->pages[i].pid = 0;
		invTable->pages[i].page = 0;
		invTable->pages[i].time_created = t;
		// printf("time created: %d\n", invTable->pages[i].time_created);
	}
}

int translate(struct inv_table invTable, int pid, int page, int offset) {
	int oldest_creation = invTable.pages[0].time_created;

	for (int i = 0; i < invTable.number_of_pages; ++i)
	{
		if (invTable.pages[i].pid == pid && invTable.pages[i].page == page)
		{
			// printf("INSIDE IF\n");
			return i;
		}
		else if (invTable.pages[i].pid == 0 && invTable.pages[i].page == 0)
		{
			// printf("INSIDE ELSE IF\n");
			invTable.pages[i].pid = pid;
			invTable.pages[i].page = page;
			return i;
		}
	}

	time_t t;
	int index = 0;
	for (int i = 0; i < invTable.number_of_pages; ++i)
	{
		if (invTable.pages[i].time_created < oldest_creation)
		{
			oldest_creation = invTable.pages[i].time_created;
			index = i;
		}
	}

	t = time(NULL);
	invTable.pages[index].pid = pid;
	invTable.pages[index].page = page;
	invTable.pages[index].time_created = t;

	return index;
}

void releaseInverted(struct inv_table *invTable){
	free(invTable->pages);
	// free(invTable);
}