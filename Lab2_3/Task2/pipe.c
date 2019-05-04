#include	<sys/types.h>
#include <sys/wait.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>

#define MAXLINE 1024
#define	oops(m,x)	{ perror(m); exit(x); }

int main(void)
{
	int		n, fd[2];
	pid_t	pid;
	char	line[MAXLINE];
	char	line2[MAXLINE];
	char 	buf[MAXLINE];

	while(strcmp(line, "stop\n") != 0) {
		if (pipe(fd) < 0)
			printf("Cannot create a pipe.");

		if ( (pid = fork()) < 0)
			printf("Cannot fork.");
		else if (pid == 0) /* child */
		{
			read(fd[0], line, MAXLINE);
			//n = read(fd[0], line, MAXLINE);
			//printf("I am reading insdie the child\n");
			printf("PID %d Recieved Message: %s", getpid(), line);
			close(fd[0]);
		}
		else /* parent */
		{
			printf("Enter message:\n");
			fgets(line, MAXLINE, stdin);
			write(fd[1], line, MAXLINE);
			//n = read(fd[0], line, MAXLINE);
			printf("PID %d Sending Message: %s", getpid(), line);
			//printf("I am reading insdie the parent\n");
			//printf("pid %d Sending message: \"%s\" to child", getpid(), line2);
			close(fd[1]);
			wait(NULL);
		}
	}
}
