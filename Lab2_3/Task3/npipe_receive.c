#include	"npipe.h"

int main(int argc, char** argv) {
	char line[MAX_LINE];
	int pipe;
	
	// open a named pipe
	pipe = open("/tmp/ajsFIFO", O_RDONLY);
	
   // set the mode to blocking (note '~')
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
	
	// close the pipe
	close(pipe);
	return 0;
}