#include	<errno.h>
#include	<sys/types.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include <sys/wait.h>
#define oops(m) ({fprintf(stderr, "ERROR: %s\n", m); exit(-1);})
int main()
{
   pid_t pid11, pid111, pid112, pid12, pid121, pid122;
   
	/* fork a child process */
	pid11 = fork(); //1.1
   
	if (pid11 < 0) /* error occurred */
		oops("Fork Failed!");
   
	else if (pid11 == 0) { /* child process */ //1.1
		printf("I am the child 1.1: %d\n",getpid());
		// if (execlp("./iam","iam", "Hello Parent! Please do not kill me!",NULL) < 0)
		//    oops("Execlp Failed!");
		
		pid111 = fork(); //1.1.1

		if (pid111 < 0)
		{
			oops("Fork Failed");
		}
		else if (pid111 == 0)
		{
			printf("I am the child 1.1.1: %d, my parent is %d\n",getpid(), getppid());
		}
		else
		{
			pid112 = fork();

			if (pid111 < 0)
			{
				oops("Fork Failed");
			}
			else if (pid111 == 0)
			{
				printf("I am the child 1.1.1: %d, my parent is %d\n",getpid(), getppid());
			}
			else
			{
				if (wait(NULL) < 0)
     				printf("-1 from wait(NULL) with errno = %d\n", errno);
     			else
     			{
					printf("Child 1.1.2 complete\n");
				}
			}

			if (wait(NULL) < 0)
     			printf("-1 from wait(NULL) with errno = %d\n", errno);
     		else
     		{
				printf("Child 1.1.1 complete\n");
			}
		}
		
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		printf("I am the parent %d\n",getpid());
      if (wait(NULL) < 0)
         printf("-1 from wait(NULL) with errno = %d\n", errno);
		
		printf("Child 1.1 Complete\n");

		pid12 = fork();

		if (pid12 < 0)
		{
			oops("Fork Failed");
		}
		else if (pid12 == 0)
		{
			printf("I am the child 1.2: %d, my parent is %d\n",getpid(), getppid());

			pid121 = fork();

			if (pid121 < 0)
			{
				oops("Fork Failed");
			}
			else if (pid121 == 0)
			{
				printf("I am the child 1.2.1: %d, my parent is: %d\n", getpid(), getppid());
			}
			else
			{
				pid122 = fork();

				if (pid122 < 0)
				{
					oops("Fork Failed");
				}
				else if (pid122 == 0)
				{
					printf("I am the child 1.2.2: %d, my parent is: %d\n", getpid(), getppid());
				}
				else
				{
					if (wait(NULL) < 0)
         				printf("-1 from wait(NULL) with errno = %d\n", errno);
         			else
         			{
						printf("Child 1.2.2 complete\n");
					}
				}

				if (wait(NULL) < 0)
         			printf("-1 from wait(NULL) with errno = %d\n", errno);
         		else
         		{
					printf("Child 1.2.1 complete\n");
				}
			}
		}
		else
		{
			printf("I am the parent of 1.2\n");

			if (wait(NULL) < 0)
         		printf("-1 from wait(NULL) with errno = %d\n", errno);
         	else
         	{
				printf("Child 1.2 complete\n");
			}
		}

		exit(0);
	}
}
