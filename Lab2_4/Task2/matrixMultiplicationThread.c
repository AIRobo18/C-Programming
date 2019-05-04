#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIZE 1024

int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE], c[MAX_SIZE][MAX_SIZE];
int m, k, n;

struct v { 
	int r; 
	int c; 
};

void *matrixThread(void *cellIndex);
void loadMatrices(char *fileName);
void loadMatrix(FILE*, int [][MAX_SIZE], int, int);
void multiply(int [][MAX_SIZE], int[][MAX_SIZE], int[][MAX_SIZE], int, int, int);
void displayMatrix(int [][MAX_SIZE], int, int);

/*
	Creates the threads to compute the operation for each cell
*/
void *matrixThread(void *cellIndex) {
	struct v ci = *(struct v*)cellIndex;
	int sum = 0;

	for (int i = 0; i < k; ++i) {
		sum += a[ci.r][i] * b[i][ci.c];
	}

	c[ci.r][ci.c] = sum;

	// for(int r = 0; r < m; r++){
	// 	for(int j = 0; j < n; j++){
	//  		sum=0;
	//    		for(int i = 0; i < k; i++){
	//     		sum = sum + a[r][i] * b[i][r];
	//    		}
	//   		c[r][j] = sum;
	//   		sum=0;
	//  	}
	// }

	pthread_exit(NULL);
}

/* 	
	Reads the info in the file
	It gets the number of rows and cols, and calls the loadMatrix 
*/
void loadMatrices(char *fileName) {
	FILE *fp = fopen(fileName, "r");

	if (fp) {
		fscanf(fp, "%d", &m);
		fscanf(fp, "%d", &k);
		fscanf(fp, "%d", &n);
		printf("M: %d, K: %d, N: %d\n", m, k, n);
		printf("\nMATRIX A\n");
		loadMatrix(fp, a, m, k);
		displayMatrix(a, m, k);
		printf("\nMATRIX B\n");
		loadMatrix(fp, b, k, n);
		displayMatrix(b, k, n);

		fclose(fp);
	}
}

/*
	Creates the single matrix and stores it into one of the global matrices
*/
void loadMatrix(FILE* fp, int current_matrix[][MAX_SIZE], int x, int y) {
	for (int r = 0; r < x; ++r) {
		for (int c = 0; c < y; ++c) {
			fscanf(fp, "%d", &current_matrix[r][c]);
		}
	}
}

/*
	This computes the matrix multiplication process on the first two inputed matrices and stores it into the third matrix
*/
void multiply(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int m, int k, int n) {
	int rc;

	//struct v *vector = malloc(sizeof(struct v));
	struct v vector;

	pthread_t tid[m*n]; /* Thread ID */
	int threadIndicy = 0;
	pthread_attr_t attr; /* Set of thread attributes */

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); /* means threads will be joined later on */

	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			//vector->r = r;
			//vector->c = c;
			vector.r = r;
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

	// pthread_attr_destroy(&attr);
	// pthread_exit(NULL);
}

void displayMatrix(int current_matrix[][MAX_SIZE], int x, int y) {
	for (int r = 0; r < x; ++r) {
		for (int c = 0; c < y; ++c) {
			printf("%d ", current_matrix[r][c]);
		}
		printf("\n");
	}
}

int main() {
	loadMatrices("input.txt");
	multiply(a, b, c, m, k, n);
	printf("\nMATRIX C\n");
	displayMatrix(c, m, n);
	return 0;
}