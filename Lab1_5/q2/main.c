//
//  main.c
//  scannerTable
//
//  Created by Robert Aroutiounian on 10/3/16.
//  Copyright © 2016 AIR. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#define BUFF 156
#define COLNUM 47
#define ROWNUM 13

int main(int argc, const char * argv[]) {
	//	char **trans_table;
	//	FILE *trans_in_file = fopen(argv[i+1], "r");
	//
	//	if (trans_in_file == NULL)
	//		exit(-1);
	//
	//	scan_init(trans_in_file, &trans_table);
	//
	//	while (not_end)
	//		display_token(scan(trans_table));
	
	char trans_table[ROWNUM][COLNUM];
	char *temp[BUFF];
	FILE *trans_in_file = fopen(argv[1], "r");
	
	if (trans_in_file == NULL) {
		exit(-1);
	}
	
	int i,j;
	char c;
	int row = 0;
	int col = 0;
	
	while(1) {
		c = fgetc(trans_in_file);
		if (feof(trans_in_file)) {
			break;
		}
		//printf("inside while");
		if (c == '\n') {
			row++;
			col = 0;
		}
		
		while (c != ' ' && !feof(trans_in_file)) {
			//printf("inside while 1 ");
			if (c == ' ') {
				printf("c is a space \n");
			}
			else
				printf("c is not a space.\n");
			//printf("c: %c\n", c);
			trans_table[row][col++] = c;
			//printf("col: %d\n", col);
			c = fgetc(trans_in_file);
		}

		// for (col = 0; c != ' '; col++) {
		// 	printf("c: %c\n", c);
		// 	trans_table[row][col] = c;
		// 	c = fgetc(trans_in_file);
		// }
	}
	
		// while ((c = (getchar() != EOF))) {
		// 	printf("inside while");
		// 	if (c == '\n') {
		// 		row++;
		// 	}
	
		// 	for (col = 0; c != ' '; col++) {
		// 		trans_table[row][col] = c;
		// 		c = getchar();
		// 	}
		// }
	
	for (i = 0; i < row; i++) { //used to see what's inside the 2d array
		printf("insdie for i ");
		for (j = 0; j < col; j++) {
			printf("indside for j ");
			printf("%c", trans_table[i][j]);
		}
		printf("\n");
	}
	
	printf("row: %d\n", row);
	printf("col: %d\n", col);

	TOKEN *token = (TOKEN*) malloc(sizeof(TOKEN));

	int state = trans_table[0][0];
	for (i = 0; i < ROWNUM; i++)
	{
		for (j = 0; j < COLNUM; )
		{
			if (trans_table[i][j] == 'a')
			{
				
			}
		}
	}
}
