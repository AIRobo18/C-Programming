/* % must be in the first column (no indentation) */

/* to avoid warnning about yywrap() if we do not need it */
%option noyywrap

%{ // must start in the first column
   #include "l7t1.h"
   int number_of_target_words = 0; // TODO: complete
//   double sum_of_numbers = 0; // TODO: complete
//   double totDol = 0;
   double numChar;
   int targetArr[9];
%} // must start in the first column

/* aliasses */
letter [A-Za-z]
digit [0-9]
number ({digit})+(\.)?({digit})*
word {letter}+ 

/* matching rules */
%%

"bank" 	{/* match action */ 
				number_of_target_words++;
				printf("<!>");
				ECHO;
				printf("<!>\n");
				targetArr[BANK] += 1;
				return BANK;
			}

"dollar" 	{
				number_of_target_words++;
				printf("<!>");
				ECHO;
				printf("<!>\n");
				targetArr[DOLLAR] += 1;
				return DOLLAR;
			} // TODO: complete

"finance"	{
					number_of_target_words++;
					printf("<!>");
					ECHO;
					printf("<!>\n");
					targetArr[FINANCE] += 1;
					return FINANCE;
				}

"budget" 	{
					number_of_target_words++;
					printf("<!>");
					ECHO;
					printf("<!>\n");
					targetArr[BUDGET] += 1;
					return BUDGET;
				}

"fund" 	{
					number_of_target_words++;
					printf("<!>");
					ECHO;
					printf("<!>\n");
					targetArr[FUND] += 1;
					return FUND;
				}

"stock" 	{
					number_of_target_words++;
					printf("<!>");
					ECHO;
					printf("<!>\n");
					targetArr[STOCK] += 1;
					return STOCK;
				}

"bond" 	{
				number_of_target_words++;
				printf("<!>");
				ECHO;
				printf("<!>\n");
				targetArr[BOND] += 1;
				return BOND;
			}

"invest" {
								number_of_target_words++;
								printf("<!>");
								ECHO;
								printf("<!>\n");
								return INVEST;
							}

(\${number})  {
				numChar = strtod(yytext+1, NULL);
				totDol +=  numChar;
				sum_of_numbers += numChar;
				printf("<$>%.2lf<$>\n", numChar);
			} // TODO: complete

({number})	{
				numChar = strtod(yytext, NULL);
				sum_of_numbers += numChar;
				printf("<#>%.2lf<#>\n", numChar);
			}

%%