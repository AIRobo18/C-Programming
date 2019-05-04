%option noyywrap

%{
#include "l7t2.h"
%}

letter [a-z]
digit [0-9]
addOp [-+]
multOp [/%*]
%%

"if" {return IF;}
"then" {return THEN;}
"while" {return WHILE;}
"do" {return DO;}
"print" {return PRINT;}
%%