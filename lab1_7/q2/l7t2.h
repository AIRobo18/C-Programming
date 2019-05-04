#ifndef l7t2_h_
#define l7t2_h_

#include <stdio.h>

typedef enum {
   IF = 258, // since Bison will start tokens at that number
   THEN,
   WHILE,
   DO,
   PRINT
   // and so on...
} TOKEN;

#endif