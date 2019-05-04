#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef enum {
	PRIORITY_HIGH = 99,
	PRIORITY_MEDIUM = 50,
	PRIORITY_LOW = 1
} PRIORITY;

int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;

	// get the default attributes
	pthread_attr_init(&attr);

	// specialize attributes
	PRIORITY schedparam_h = PRIORITY_HIGH;
	PRIORITY schedparam_m = PRIORITY_MEDIUM;
	PRIORITY schedparam_l = PRIORITY_LOW;

	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	pthread_attr_setschedparam(&attr, &schedparam_h);

	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	pthread_attr_setschedparam(&attr, &schedparam_m);

	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
	pthread_attr_setschedparam(&attr, &schedparam_l);


	pthread_create(&tid, &attr, &runner, &argv);

	
	pthread_join(tid, NULL);
	pthread_attr_destroy(&attr);

	return 0;
}