//
//  main.c
//  l5t1
//
//  Created by Aroutiounian, Robert on 9/28/16.
//  Copyright © 2016 Aroutiounian, Robert. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

int main(int argc, const char * argv[]) {

	TOKEN *token;
	
	if (argc > 1) {
		if (freopen(argv[1], "r", stdin) == NULL) {
			printf("Error in input\n");
			exit(-1);
		}
	}
	// else
	// 	fp = stdin;

		
	while ((token = scanner()) != NULL) {
		if (token->type == IDENTTOKEN) {
			printf("{<%s> %s}, ", token_names[0], token->attributes.name);
		}
		else if (token->type == NUMBERTOKEN) {
			printf("{<%s> %d}, ", token_names[1], token->attributes.intVal);
		}
		else if (token->type == ASSIGNMENT) {
			printf("{<%s>}, ", token_names[2]);
		}
		else if (token->type == SEMICOLON) {
			printf("{<%s>}, ", token_names[3]);
		}
		else if (token->type == LPAREN) {
			printf("{<%s>}, ", token_names[4]);
		}
		else if (token->type == RPAREN) {
			printf("{<%s>}, ", token_names[5]);
		}
		else if (token->type == PLUS) {
			printf("{<%s>}, ", token_names[6]);
		}
		else if (token->type == MINUS) {
			printf("{<%s>}, ", token_names[7]);
		}
		else if (token->type == MULT) {
			printf("{<%s>}, ", token_names[8]);
		}
		else if (token->type == DIV) {
			printf("{<%s>}, ", token_names[9]);
		}
		else if (token->type == MOD) {
			printf("{<%s>}, ", token_names[10]);
		}
		else if (token->type == REPEAT) {
			printf("{<%s> repeat}, ", token_names[11]);
		}
		else if (token->type == PRINT) {
			printf("{<%s> print}, ", token_names[11]);
		}
		// else {
		// 	printf("Nothing happened");
		// }
	}
	printf("\n");
}