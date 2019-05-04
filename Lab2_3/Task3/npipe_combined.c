#include	"npipe.h"

int main(int argc, char** argv) {
	char line[MAX_LINE];
	int pipe;
	
	int stat;
	if (stat = mkfifo("/tmp/ajsFIFO", 0600) < 0) {
		pipe = open("/tmp/ajsFIFO", O_RDONLY);
		//oops("Cannot make FIFO", stat);
		int flags;
	   flags &= ~O_NONBLOCK;
	   //flags |= O_NONBLOCK;
	   fcntl(pipe, F_SETFL, flags);
	   
	   while(1){
			// read the data from the pipe
			read(pipe, line, MAX_LINE);

			if (strcmp(line, "quit\n") == 0)
				break;
			
			printf("Received line: %s\n", line);
		}
	}
	
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