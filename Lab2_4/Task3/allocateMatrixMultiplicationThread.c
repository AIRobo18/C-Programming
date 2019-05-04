#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int **a, **b, **c;
int m, k, n;

struct v { 
	int r; 
	int c; 
};

void *matrixThread(void *cellIndices);
void allocateAndLoadMatrices(char *fileName);
void loadMatrix(FILE*, int **, int, int);
void multiply(int **, int**, int**, int, int, int);
void displayMatrix(int**, int, int);

void *matrixThread(void *cellIndices) {
	struct v ci = *(struct v*)cellIndices;
	int sum = 0;

	for (int i = 0; i < k; ++i) {
		sum += a[ci.r][i] * b[i][ci.c];
	}

	c[ci.r][ci.c] = sum;

	pthread_exit(NULL);
}

/*
	Reads the info from the file
*/
void allocateAndLoadMatrices(char *fileName) {
	FILE *fp = fopen(fileName, "r");

	if (fp) {
		fscanf(fp, "%d", &m);
		fscanf(fp, "%d", &k);
		fscanf(fp, "%d", &n);
		printf("M: %d, K: %d, N: %d\n", m, k, n);

		a = (int **)malloc(sizeof(int *) * m); /* Allocate memory for the row */
		for (int i = 0; i < m; ++i) { /* Allocating memory for the columns of each row */
			a[i] = (int *)malloc(sizeof(int) * k);
		}
		printf("\nMATRIX A\n");
		loadMatrix(fp, a, m, k);
		displayMatrix(a, m, k);

		b = (int **)malloc(sizeof(int *) * k); /* Allocate memory for the row */
		for (int i = 0; i < k; ++i) { /* Allocating memory for the columns of each row */
			b[i] = (int *)malloc(sizeof(int) * n);
		}
		printf("\nMATRIX B\n");
		loadMatrix(fp, b, k, n);
		displayMatrix(b, k, n);

		c = (int **)malloc(sizeof(int *) * m); /* Allocate memory for the row */
		for (int i = 0; i < m; ++i) { /* Allocating memory for the columns of each row */
			c[i] = (int *)malloc(sizeof(int) * n);
		}

		fclose(fp);
	}
}

/*
	Loads the numbers from the file into the multidimensional arrays
	currentMatric is the address of a or b
*/
void loadMatrix(FILE* fp, int **currentMatrix, int x, int y) {
	for (int r = 0; r < x; ++r) {
		for (int c = 0; c < y; ++c) {
			fscanf(fp, "%d", &currentMatrix[r][c]);
		}
	}
}

void multiply(int **a, int **b, int **c, int m, int k, int n) {
	int rc;

	struct v vector;

	pthread_t tid[m*n]; /* Thread ID */
	int threadIndicy = 0;
	pthread_attr_t attr; /* Set of thread attributes */

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); /* means threads will be joined later on */

	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			vector.r =r; 
			vector.c = c;

			rc = pthread_create(&tid[threadIndicy], &attr, matrixThread, (void*)&vector);
			threadIndicy++;
			if (rc) {
				printf("ERROR: return code from pthread_create() is %d\n", rc);
				exit(-1);
			}
		}
	}

	for (int i = 0; i < threadIndicy; ++i)
	{
		rc = pthread_join(tid[i], NULL);
		if (rc)
		{
			printf("ERROR: return code from pthread_join is %d\n", rc);
			exit(-1);
		}
	}
}

void displayMatrix(int **currentMatrix, int x, int y) {
	for (int r = 0; r < x; ++r) {
		for (int c = 0; c < y; ++c) {
			printf("%d ", currentMatrix[r][c]);
		}
		printf("\n");
	}
}

int main() {
	allocateAndLoadMatrices("input.txt");
	multiply(a, b, c, m, k, n);
	printf("\nMATRIX C\n");
	displayMatrix(c, m, n);
	return 0;
}