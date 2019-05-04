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
#define NUM_OF_TESTS 55

extern void initInverted(struct inv_table *invTable, int memSize, int frameSize);
extern int translate(struct inv_table invTable, int pid, int page, int offset);
extern void releaseInverted(struct inv_table *invTable);
extern struct inv_table table;
extern struct inv_table_page table_page;

int main(int argc, char const *argv[]) {
	// struct inv_table table;
	// struct inv_table_page table_page;

	initInverted(&table, MEM_SIZE, FRAME_SIZE);

	int ran_pid;
	int ran_page;
	int ran_offset;
	int index;

	for (int i = 0; i < NUM_OF_TESTS; ++i)
	{
		ran_pid = rand() % (PID + 1 - 1) + 1;
		ran_page = rand() % (PAGE + 1 - 1) + 1;
		ran_offset = rand() % (OFFSET + 1 - 1) + 1;
		while (ran_offset > FRAME_SIZE) {
			ran_offset = rand() % (OFFSET + 1 - 1) + 1;
		}

		printf("\nLOGICAL ADDRESS\n");
		printf("PID: %d | Page: %d | Offset: %d\n", ran_pid, ran_page, ran_offset);

		index = translate(table, ran_pid, ran_page, ran_offset);
		printf("\nPHYSICAL ADDRESS\n");
		printf("Index: %d | Offset: %d\n", index, ran_offset);
	}

	releaseInverted(&table);

	// initInverted(&table, MEM_SIZE, FRAME_SIZE);
	return 0;
}