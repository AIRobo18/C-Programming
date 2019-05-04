#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#define SCHEDULE_NAME_LENGTH 5
#define MAX_LEN 1024
#define NUM_0F_PROCESSES 4

int burst_times[MAX_LEN];
int quantum_time;
int quantum_tick;
int burst_size;

int fcfs(int index);
int sjf(int index);
int srtf(int index);
int rr(int index, int q_time);
void display(int tick, int index, int j);

int fcfs(int index) {
	for (int i = index; i < NUM_0F_PROCESSES; ++i)
	{
		if (burst_times[i] != 0) {
			return i;
		}
		return i + 1;
	}
	return -1;
}

int sjf(int index) {
	if (burst_times[index] != 0)
	{
		return index;
	}
	else {
		int i = 0;
		while(burst_times[i] == 0) {
			i++;
		}
		int min_val = burst_times[i];
		int min_index = i;
		for (int j = 0; j < NUM_0F_PROCESSES; ++j)
		{
			if (burst_times[j] < min_val && burst_times[j] != 0)
			{
				burst_times[i] = burst_times[j];
				min_val = burst_times[j];
				min_index = j;
			}
		}
		return min_index;
	}
	return -1;
}

int srtf(int index) {
	int curr = -1;
	if (burst_times[index] == 0)
	{
		index = sjf(index);
	}
	for (int i = 0; i < NUM_0F_PROCESSES; ++i)
	{
		if (burst_times[i] < burst_times[index] && burst_times[i] > 0)
		{
			curr = i;
			break;
		}
		else if (burst_times[index] < 0)
		{
			curr = i;
		}
		else {
			curr = index;
		}
	}
	return curr;
}

int rr(int index, int q_time) {
		if (q_time > 0 && burst_times[index] != 0) {
			q_time--;
			quantum_tick = q_time;
			return index;
		}
		else {
			quantum_tick = quantum_time;
			for (int i = 0; i < NUM_0F_PROCESSES; ++i)
			{
				if (burst_times[i] != 0 && i != index)
				{
					return i;
				}
			}
		}

	return -1;
}

void display(int tick, int index, int j) {
	printf("T%d:\n", tick);
	printf("CPU: P%d(%d)\n", index + 1, burst_times[index]);
	printf("QUEUE:");
	for (int i = 0; i < j; ++i)
	{
		if (i != index && burst_times[i] != 0) {
			printf(" P%d(%d)", i+1, burst_times[i]);
		}
		// else {
		// 	printf("<empty>");
		// }
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int index = 0;
	int j = 0;
	int next_arrival_time;
	int time_tick = 0;
	char schedule_algorithm[SCHEDULE_NAME_LENGTH];

	FILE *fp = fopen("input.txt", "r");

	if (fp) {
		fscanf(fp, "%s", schedule_algorithm);
		if (strcmp(schedule_algorithm, "RR") == 0) {
			fscanf(fp, "%d", &quantum_time);
			quantum_tick = quantum_time;
		}
		fscanf(fp, "%d", &next_arrival_time);

		int isEmpty = 1;
		while(!feof(fp) || burst_times[index] != 0 || isEmpty){
			if (next_arrival_time == time_tick) {
				fscanf(fp, "%d", &burst_times[j]);
				fscanf(fp, "%d", &next_arrival_time);
				j++;
				display(time_tick, index, j);
			}

			if (strcmp(schedule_algorithm, "FCFS") == 0) {
				index = fcfs(index);
			}
			else if (strcmp(schedule_algorithm, "SJF") == 0) {
				index = sjf(index);
			}
			else if (strcmp(schedule_algorithm, "SRTF") == 0) {
				index = srtf(index);
			}
			else if (strcmp(schedule_algorithm, "RR") == 0) {
				index = rr(index, quantum_tick);
			}

			if (index != -1) {
				burst_times[index]--;
			}
			if (burst_times[index] == 0 && index != -1) {
				display(time_tick, index, j);
			}
			for (int i = 0; i < NUM_0F_PROCESSES; ++i)
			{
				if (burst_times[i] != 0)
				{
					break;
				}
				else if (burst_times[i = NUM_0F_PROCESSES -1] == 0)
				{
					isEmpty = 0;
				}
			}
			time_tick++;
		}
	}
	
	return 0;
}