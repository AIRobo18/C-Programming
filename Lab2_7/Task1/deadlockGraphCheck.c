#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LEGNTH 251

int label_search(char *vertex_label, char **vertex_array, int size_of_array);

int main() {
	//char *input_vertices = "V={Aa, Bbb, Cccc, Ddddd}";
	char input_vertices[MAX_INPUT_LEGNTH];
	//char *input_edges = "E={{Aa, Cccc}, {Aa, Ddddd}, {Bbb, Cccc}, {Cccc, Bbb}, {Cccc, Ddddd}, {Ddddd, Aa}, {Ddddd, Cccc}}";
	char input_edges[MAX_INPUT_LEGNTH];
	char *delim = " ={},";
	char *rest;
	char *rest2;
	char *next;
	char temp_vertices[MAX_INPUT_LEGNTH][MAX_INPUT_LEGNTH];
	char temp_edges[MAX_INPUT_LEGNTH][MAX_INPUT_LEGNTH];
	char **vertices;
	char **edges;
	int v_count = 0;
	int e_count = 0;

	/* Step 1 sorta done, need to read in line using fgets instead of hardcoding V and E */
	FILE *fp = fopen("input.txt", "r");
	fgets(input_vertices, MAX_INPUT_LEGNTH, fp);
	// printf("%s\n", input_vertices);
	fgets(input_edges, MAX_INPUT_LEGNTH, fp);
	fclose(fp);
	rest = strdup(input_vertices);
	while (rest != NULL) {
		next = strsep(&rest, delim);

		if (*next != '\0' && *next != 'V') {
			strcpy(temp_vertices[v_count], next);
			v_count++; 
		}
	}
	v_count--;

	vertices = malloc(sizeof(char *) * v_count);
	for (int i = 0; i < v_count; ++i)
	{
		vertices[i] = malloc(sizeof(char) * MAX_INPUT_LEGNTH);
		strcpy(vertices[i], temp_vertices[i]);
	}

	// for (int i = 0; i < v_count; ++i)
	// {
	// 	printf("%s ", vertices[i]);
	// }

	rest2 = strdup(input_edges);
	while (rest2 != NULL) {
		next = strsep(&rest2, delim);

		if (*next != '\0' && *next != 'E') {
			strcpy(temp_edges[e_count], next);
			e_count++;
		}
	}

	edges = malloc(sizeof(char *) * e_count);
	for (int i = 0; i < e_count; ++i)
	{
		edges[i] = malloc(sizeof(char) * MAX_INPUT_LEGNTH);
		strcpy(edges[i], temp_edges[i]);
		// printf("%s %s\n", edges[i], temp_edges[i]);
	}

	// for (int i = 0; i < e_count; ++i)
	// {
	// 	printf("%s %s\n ", edges[i], edges[i+1]);
	// 	i++;
	// }


	/* Step 2 DONE: created an n x n adjacentcy matrix with 0s where n is length of V */
	int adj_matrix[v_count][v_count];
	// printf("%d\n", v_count);
	for (int i = 0; i < v_count; ++i) {
		for (int j = 0; j < v_count; ++j) {
			adj_matrix[i][j] = 0;
		}
	}

	int first_index;
	int second_index;
	for (int i = 0; i < e_count; ++i) {
		first_index = label_search(edges[i], vertices, v_count);
		second_index = label_search(edges[i + 1], vertices, v_count);
		adj_matrix[first_index][second_index] = 1;
		i++;
	}

	for (int i = 0; i < v_count; ++i)
	{
		for (int j = 0; j < v_count; ++j)
		{
			printf("%d ", adj_matrix[i][j]);
		}
		printf("\n");
	}

	int initial_vertex;
	int initial_edge;
	for (int i = 0; i < v_count; ++i)
	{
		for (int j = 0; j < v_count; ++j)
		{
			if (adj_matrix[i][j] == 1)
			{
				initial_vertex = i;
				initial_edge = j;
				break;
			}
		}
	}

	int visited_matrix[v_count][v_count];
	for (int i = 0; i < v_count; ++i) {
		for (int j = 0; j < v_count; ++j) {
			if (adj_matrix[i][j] == 1) {
				if (visited_matrix[i][j] == 1) {
					printf(">> DEADLOCKED <<\n");
					return 0;
				}
				visited_matrix[i][j] = 1;
				i = j;
				j = 0;
			}
		}
	}
	printf(">> NO DEADLOCK <<\n");
}

int label_search(char *vertex_label, char **vertex_array, int size_of_array) {
	for (int i = 0; i < size_of_array; ++i) {
		if (strcmp(vertex_array[i], vertex_label) == 0) {
			return i;
		}
	}

	return 0;
}























