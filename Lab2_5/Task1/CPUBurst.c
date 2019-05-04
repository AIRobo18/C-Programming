#include <stdlib.h>
#include <stdio.h>
#define MAX_NUMBER_OF_BURSTS 1024

int main(int argc, char const *argv[])
{
	double t_curr, t_pre, alpha;

	printf("Enter the alpha:\n");
	scanf("%lf", &alpha);

	printf("Enter the CPU bursts:\n");
	scanf("%lf", &t_curr);

	while(!feof(stdin)) {
		t_pre = t_curr;
		scanf("%lf", &t_curr);
		t_curr = (alpha * t_curr) + t_pre * (1 - alpha);
		printf("Current: %lf\n", t_curr);
	}
	return 0;
}