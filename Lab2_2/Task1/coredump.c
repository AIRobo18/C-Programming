#include <stdio.h>
int offensiveFunc(int, int);

int main(void)
{
   printf("The next line will cause core dump.\n");
   printf("ERROR: %d\n", offensiveFunc(8.0, 4.0));
   return 0;
}

int offensiveFunc(int x, int y)
{
	if (y==0) {
		printf("You cannot have a negative denominator");
		
		return -1;
	}
	else {
   		int z = x / y;
   		return z;
   	}
}
