#include	"npipe.h"

int main(int argc, char** argv) {
	char line[MAX_LINE];
	int pipe;
	
	int stat;
	if (stat = mkfifo("/tmp/ajsFIFO", 0600) < 0)
		oops("Cannot make FIFO", stat);
	
	// open a named pipe
	pipe = open("/tmp/ajsFIFO", O_WRONLY);
	
	while(1)
	{
		// get a line to send
		printf("Enter line: ");
		fgets(line, MAX_LINE, stdin);

		// actually write out the data and close the pipe
		write(pipe, line, strlen(line));
		
		if (strcmp(line, "quit\n") == 0)
			break;
	}

	unlink("/tmp/ajsFIFO");

	// close the pipe
	close(pipe);

	return 0;
}