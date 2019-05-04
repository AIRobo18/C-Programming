//
//  main.c
//  scanner
//
//  Created by Aroutiounian, Robert on 9/28/16.
//  Copyright © 2016 Aroutiounian, Robert. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

int isKeyword(TOKEN *token, char *str) {
	if( strcmp( str, "repeat" ) == 0 )
		token->type = REPEAT;
	else if( strcmp( str, "print" ) == 0 )
		token->type = PRINT;
	else
		return 0;
	
	return 1;
}

TOKEN *scanner(FILE *fileStream) {
	TOKEN *token = (TOKEN*) malloc(sizeof(TOKEN));
	char word[BUF_SIZE];
	
	token->type = INVALID_TOKEN;
	token->attributes.name = NULL;
	token->attributes.intVal = 0.0;
	
	char c;
	int i;
	int state = 1;
	
	while ((token->type == INVALID_TOKEN) && ((c = getchar()) != EOF )) {
		switch (state) {
			case 1:
				switch (c) {
					case ' ':
					case '\t':
					case '\n':
						break;
					case '=':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = ASSIGNMENT;
						break;
					case ';':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = SEMICOLON;
						break;
					case '(':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = LPAREN;
						break;
					case ')':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = RPAREN;
						break;
					case '+':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = PLUS;
						break;
					case '-':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = MINUS;
						break;
					case '*':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = MULT;
						break;
					case '/':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = DIV;
						break;
					case '%':
						token->attributes.name = malloc(sizeof(char));
						token->attributes.name[0] = c;
						token->type = MOD;
						break;
					case 'a'...'z':
						//printf("IN ALPHABET CASE\n");
						state = 2;
						ungetc(c, stdin);
						break;
					case '0'...'9':
						state = 3;
						ungetc(c, stdin);
						break;
					default:
						printf("INVALID INPUT: %c", c);
						break;
				}
				break;
			case 2:
				//printf("IN CASE 2\n");
				i = 0;
				do {
					word[i++] = c;
					c = getchar();
				} while (isalpha(c));
				word[i] = '\0';
				ungetc(c, stdin);
				if (!isKeyword(token, word)) {
					token->type = IDENTTOKEN;
					token->attributes.name = (char *)(malloc(strlen(word) + 1));
					strcpy(token->attributes.name, word);
					state = 1;
				}
				//return token;
				break;
			case 3:
				//printf("IN CASE 3\n");
				i = 0;
				do {
					word[i++] = c;
					c = getchar();
				} while (isdigit(c));
				word[i] = '\0';
				ungetc(c, stdin);
				token->type = NUMBERTOKEN;
				//int r;
				token->attributes.intVal = atoi(word);//sscanf(word, "%d", &r);
				state = 1;
				//return token;
				break;
			default:
				printf("INVALID STATE");
				break;
		}
	}
	if (c == EOF) {
		//free(token);
		return NULL;
	}
	return token;
}
