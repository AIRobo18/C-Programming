// Robert Aroutiounian
//Lab1 Task3
// 2/2/17

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FROM_CHAR 1
#define TO_CHAR 2

int main(int argc, char *argv[])
{
	int ctr;
	char fromChar;
	char toChar;
	FILE *inFile;
	FILE *outFile;
	// We will need feof, putc, getc
	// while(!foef(stdin)) { char c = getc(stdin); putc(c, stdout); }
	
	if (argc > 1) {
		if ((strcmp(argv[FROM_CHAR], "-h")) == 0) {
			printf("sub fromChar ToChar [-f inputFile] [-o outputFile]\n");
		}
		else {
			fromChar = argv[FROM_CHAR][0];
			toChar = argv[TO_CHAR][0];

			inFile = stdin;
			outFile = stdout;

			for (ctr = 3; ctr < argc; ctr++) {
				if ((strcmp(argv[ctr], "-f")) == 0) {
					if (argv[ctr + 1] == NULL)
					{
						printf("No input file found.\n");
						return(1);
					}
					else {
						ctr++;
						inFile = freopen(argv[ctr], "r", stdin);
					}
				}
				else if ((strcmp(argv[ctr], "-o")) == 0) {
					if (argv[ctr + 1] == NULL)
					{
						printf("No output file found\n");
						return(1);
					}
					else {
						ctr++;
						outFile = freopen(argv[ctr], "w", stdout);
					}
				}
				else {
					printf("sub fromChar ToChar [-f inputFile] [-o outputFile]\n");
					exit(0);
				}
			}

			while(!feof(inFile)) {
				char c = getc(inFile);
				if (c == fromChar) {
					putc(toChar, outFile);
				}
				else {
					putc(c, outFile);
				}
			}
			fclose(inFile);
			fclose(outFile);

			// while(!feof(stdin)) {
			// 	char c = getc(stdin);
			// 	if (c == fromChar) {
			// 		putc(toChar, stdout);
			// 	}
			// 	else {
			// 		putc(c, stdout);
			// 	}
			// }
			// fclose(stdin);
			// fclose(stdout);
		}
	}
}
