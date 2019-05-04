#include "l7t2.h"

int main(void) {

TOKEN tok;

char *keywords[] = {"if", "then", "while", "do", "print"};

while ((tok = yylex()) != 0)
   printf("{<keyword> \"%s\">", keyword[tok - IF]);