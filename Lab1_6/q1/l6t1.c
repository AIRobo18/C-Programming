//
//  l6t1.c
//  parser
//
//  Created by Robert Aroutiounian on 10/10/16.
//  Copyright © 2016 Aroutiounian, Robert. All rights reserved.
//

#include <stdio.h>
#include "parser.h"

int child = 0;

int children (AST_NODE *node) {
	if (node->left_node != NULL) {
		child = 1;
		if (node->right_node != NULL) {
			child = 2;
			if (node->right_node->type == ADDOP || node->right_node->type == MULTOP) {
				child = 3;
			}
		}
	}
	
	return child;
}

void print_program(AST_NODE* node) {
	AST_NODE *temp = malloc(sizeof(AST_NODE));
	temp = node;
	while(temp != NULL)
	{
		printf("Traversing tree.. ");
		switch (node->type) {
			case PROGRAM:
				printf("program: children %d\n", children(node));
				break;
			case STATEMENT:
				printf("statement: children %d\n", children(node));
				break;
			case ASSIGN_STMT:
				printf("assignStmt: children %d\n", children(node));
				break;
			case REPEAT_STMT:
				printf("repeatStmt: children %d\n", children(node));
				break;
			case PRINT_STMT:
				printf("printStmt: children %d\n", children(node));
				break;
			case EXPR:
				printf("expr: children %d\n", children(node));
				break;
			case TERM:
				printf("term: children %d\n", children(node));
				break;
			case ADDOP:
				printf("addOpNode: children %d\n", children(node));
				break;
			case FACTOR:
				printf("factor: children %d\n", children(node));
				break;
			case MULTOP:
				printf("multOpNode: children %d\n", children(node));
				break;
			case IDENTIFIER:
				printf("idNode: children %d\n", children(node));
				break;
			case NUMBER:
				printf("numberNode: children %d\n", children(node));
				break;
			default:
				printf("Node type invalid\n");
				break;
		}
		print_program(temp->left_node);
		temp = temp->right_node;
	}
}

int main(int argc, const char * argv[]) {
	
	AST_NODE *fullProgram = program();
	print_program(fullProgram);
	
	return 0;
}