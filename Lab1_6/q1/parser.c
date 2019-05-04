//
//  main.c
//  parser
//
//  Created by Aroutiounian, Robert on 10/5/16.
//  Copyright © 2016 Aroutiounian, Robert. All rights reserved.
//
//
//<program> ::= <statement> | <program> <statement>
//<statement> ::= <assignStmt> | <repeatStmt> | <printStmt>
//<assignStmt> ::= <id> = <expr> ;
//<repeatStmt> ::= repeat ( <expr> ) <stmt>
//<printStmt> ::= print <expr> ;
//<expr> ::= <term> | <expr> <addOp> <term>
//<term> ::= <factor> | <term> <multOp> <factor>
//<factor> ::= <id> | <number> | - <factor> | ( <expr> )

#include <stdio.h>
#include <string.h>
#include "parser.h"

TOKEN *token;

void expect(TOKEN_TYPE type) {
	//printf("Inside except\n");
	TOKEN *currToken = scannerAdHoc();
	if (currToken->type != type) {
		error();
		exit(-1);
	}
}

int acceptTok(TOKEN_TYPE type) {
	//printf("inside acceptTok\n");
	TOKEN* currToken = scannerAdHoc();
	if (currToken->type != type) {
		//printf("Accept is false\n");
		ungetToken(&currToken);
		return 0;
	}
	else {
		ungetToken(&currToken);
		//printf("accept is true\n");
		return 1;
	}
}

AST_NODE *program() {
	printf("\nfuncProg: ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = PROGRAM;
	node->left_node = statement();
	if (node->left_node != NULL) // This will happen when statement is set to NULL
		node->right_node = program();
	return node;
}

AST_NODE *statement() {
	printf("funcStmt: ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = STATEMENT;
	token = scannerAdHoc();
	if (token)
	{
		switch (token->type) {
		case IDENTTOKEN:
			node->left_node = assignStmt(token);
			break;
		case REPEAT:
			node->left_node = repeatStmt(token);
			break;
		case PRINT:
			node->left_node = printStmt(scannerAdHoc());
			break;
		default:
			node->left_node = NULL;
			break;
		}
	}
	else
		node = NULL;
	return node;
}

AST_NODE *assignStmt(TOKEN *currToken) {
	printf("funcAssign: ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = ASSIGN_STMT;
	node->left_node = idt(currToken);
	expect(ASSIGNMENT);
	printf("to ");
	node->right_node = expr(scannerAdHoc());
	expect(SEMICOLON);
	return node;
}

AST_NODE *repeatStmt(TOKEN *currToken) {
	printf("funcRepeat: ");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = REPEAT_STMT;
	expect(LPAREN);
	node->left_node = expr(scannerAdHoc());
	expect(RPAREN);
	printf("statement: ");
	node->right_node = statement();
	return node;
}

AST_NODE *printStmt(TOKEN *currToken) {
	printf("funcPrint: ");
	//printf("Current token: %s", currToken->strVal);
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = PRINT_STMT;
	node->left_node = expr(currToken);
	expect(SEMICOLON);
	return node;
}

AST_NODE *expr(TOKEN *currToken) { //Call scanner again when calling expr
	//printf("Inside expr\n");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = EXPR;
	node->left_node = term(currToken);
	//currToken = scannerAdHoc();
	if (acceptTok(PLUS) || acceptTok(MINUS)) {
		node->right_node = addOp(scannerAdHoc());
	}
	return node;
}

AST_NODE *addOp(TOKEN *currToken) {
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = ADDOP;
	switch (currToken->type) {
		case PLUS:
			node->data.addOp = currToken->strVal[0];
			printf("addOp(%c) ", node->data.multOp);
			break;
		case MINUS:
			node->data.addOp = currToken->strVal[0];
			printf("addOp(%c) ", node->data.multOp);
			break;
		default:
			printf("Not a valid addOp");
			break;
	}
	node->right_node = expr(scannerAdHoc());
	if (node->right_node == NULL) {
		printf("ADDOP right node is NULL");
	}
	return node;
}

AST_NODE *term(TOKEN *currToken) {
	//printf("Inside term\n");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = TERM;
	node->left_node = factor(currToken);
	if (acceptTok(MULT) || acceptTok(DIV) || acceptTok(MOD)) {
		node->right_node = multOp(scannerAdHoc());
	}
	return node;
}

AST_NODE *multOp(TOKEN *currToken) {
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = MULTOP;
	switch (currToken->type) {
		case MULT:
			node->data.multOp = currToken->strVal[0];
			printf("multOp(%c) ", node->data.multOp);
			break;
		case DIV:
			node->data.addOp = currToken->strVal[0];
			printf("multOp(%c) ", node->data.multOp);
			break;
		case MOD:
			node->data.addOp = currToken->strVal[0];
			printf("multOp(%c) ", node->data.multOp);
			break;
		default:
			printf("Not a valid multOp");
			break;
	}
	node->right_node = term(scannerAdHoc());
	if (node->right_node == NULL) {
		printf("MULTOP right node is NULL");
	}
	return node;
}

AST_NODE *factor(TOKEN *currToken) {
	//printf("Inside factor\n");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = FACTOR;
	if (currToken->type == MINUS) {
		//printf("Inside first if of factor\n");
		node->left_node = factor(scannerAdHoc());
	}
	else if (currToken->type == LPAREN) {
		//printf("Inside second condition of factor\n");
		node->left_node = expr(scannerAdHoc());
		expect(RPAREN);
	}
	else if (currToken->type == NUMBERTOKEN) {
		//printf("Inside third condition of factor\n");
		node->left_node = number(currToken);
	}
	else if (currToken->type == IDENTTOKEN) {
		//printf("Inside fourth condition of factor\n");
		node->left_node = idt(currToken);
	}
	else {
		printf("nothing worked in factor\n");
	}
	return node;
}

AST_NODE *idt(TOKEN *currToken) {
	//printf("inside id\n");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = IDENTIFIER;
	strcpy(node->data.identifier, currToken->strVal);
	printf("ID(%s) ", node->data.identifier);
	return node;
}

AST_NODE *number(TOKEN *currToken) {
	//printf("inside number\n");
	AST_NODE *node = malloc(sizeof(AST_NODE));
	node->type = NUMBER;
	node->data.number = atol(currToken->strVal);
	printf("INT(%.0f) ", node->data.number);
	return node;
}

void error() {
	printf("\n UNKNOWN ERROR OCCURED JUST LIKE THIS CODE YOUR LIFE IS A MESS \n");
}
