#include "l7t1.h"

extern int number_of_target_words; // TODO: use your own name
double sum_of_numbers = 0; // TODO: use your own name
double totDol = 0;
extern double numChar;
extern int targetArr[9];

extern FILE *yyin; /* needed if using yyin in here */

char *targetWords[NUM_OF_WORDS] = {"bank", "dollar", "finance", "budget", "fund", "stock", "bond", "invest"};

int main(int argc, char *argv[])
{
  //printf("Inside main C\n");
  int i;
  yyin = freopen(argv[1], "r", stdin);

  WORD word = NO_TOK;
  while((word = yylex()) > 0)
  {
    // if ((word > 0) && (word < NUM_OF_WORDS))
    //    printf("My word is %s", targetWords[word-BANK]);
    // if the total number of dollars is greater than 1000 do the first case
    //printf("%lf\n", totDol);
  }
  if (totDol > 1000)
    {
       printf("\n\nVERY INTERESTING READING!\n");
       printf("Repoted sum of dollars: %.2lf\n", totDol);
    }
    else if (number_of_target_words >= 3 && sum_of_numbers > 1000)
    {
      printf("\n\nPOTENTIALLY INTERESTING READING!\n");
      printf("Repoted sum of numbers: %.2lf\n", sum_of_numbers);
      printf("Concordance:\n");
      for (i = 0; i < NUM_OF_WORDS; i++)
      {
        printf("%d %s\n", targetArr[word], targetWords[word-BANK]);
      }
    }
}