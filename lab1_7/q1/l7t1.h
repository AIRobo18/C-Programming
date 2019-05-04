#ifndef __l7t1_h_
#define __l7t1_h_

#include <stdio.h>

#define NUM_OF_WORDS 8
typedef enum {
	NO_TOK=0,
	BANK,
	DOLLAR,
	FINANCE,
	BUDGET,
	FUND,
	STOCK,
	BOND,
	INVEST} WORD; // TODO: complete

int sum(int[], int);
// function computing a sum of all element of an array
// the second parameter is the size of the array
double totDol;
double sum_of_numbers;
int yylex(void);

#endif