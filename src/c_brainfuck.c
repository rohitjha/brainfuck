#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "brainfuck.h"

#define USAGEMSG "c-brainfuck, Version 0.4\nCopyright (c) Rohit Jha, 2013\n\nUsage: bf [-f/-c] [-t] <filename or code>\n\t-h  display this message\n\t-f  execute program in <filename>\n\t-c  run <code> directly\n\t-t  display tape memory\n"

/* Read the file and pass it to the bf_eval() function */
void bf_readfile(char *filename) {
	FILE *file;
	int c;
	int pointer = 0;
	int size = 0;

	/* Get the size of the file */
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Error: Failed to open %s!\n", filename);
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char chars[size];

	/* Place each character from the file into the array */
	while ((c = fgetc(file)) != EOF)
		chars[pointer++] = (char) c;
	fclose(file);

	/* Evaluate the code */
	bf_eval(chars);
}

int main(int argc, char *argv[]) {
	int i = 0;
	char pipe[65536];	/* 64K tape memory */

	/* Ensure proper usage */
	if (argc < 2 || (strcmp(argv[1], "-h") == 0)) {
		printf(USAGEMSG);
		return EXIT_FAILURE;
	}

	else if((argc < 3) && (isatty(fileno(stdin))) == 1) {
		fprintf(stderr, "Error: Invalid usage!\n%s", USAGEMSG);
		return EXIT_FAILURE;
	}

	else if(isatty(fileno(stdin))) {
		char ans;
		int low;
		int high;
		
		if (strcmp(argv[1], "-f") == 0)
			bf_readfile(argv[argc-1]);
		else if (strcmp(argv[1], "-c") == 0)
			bf_eval(argv[argc-1]);

		if ( (strcmp(argv[1], "-t") == 0) || (strcmp(argv[2], "-t") == 0) ) {
			int num;
			printf ("Contents of which cells to display?\n\t[1] First 'n' cells\n\t[2] Cells in an inclusive range\n\t[3] All cells\n(Default [1]): ");
			scanf ("%d", &num);

			if (num == 1) {
				low = 0;
				printf ("Enter value of 'n': ");
				scanf ("%d", &high);

				bf_showtape(high);
			}

			else if (num == 2) {
				printf ("Enter lower limit: ");
				scanf ("%d", &low);
				printf ("Enter upper limit: ");
				scanf ("%d", &high);

				bf_showtape_range(low,high);
			}

			else if (num == 3) {
				bf_showtape(MAX_CELLS);
			}

			else {
				printf ("Invalid response. Displaying contents of first 10 cells by default.\n");
				bf_showtape(10);
			}
		}
	}

	/* Write operations to pipe and evaluate */
	else {
		while(-1 != (pipe[i++] = getchar()));
		bf_eval(pipe);
	}

	return EXIT_SUCCESS;
}


/* Sample Output:

$ bf -f -t hello_world.bf 
Hello World!
Contents of which cells to display?
	[1] First 'n' cells
	[2] Cells in an inclusive range
	[3] All cells
(Default [1]): 1
Enter value of 'n': 10
[0]  ->  0
[1]  ->  87
[2]  ->  100
[3]  ->  33
[4]  ->  10
[5]  ->  0
[6]  ->  0
[7]  ->  0
[8]  ->  0
[9]  ->  0
*/

/* Sample Output:

$ bf -c '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.'
Hello World!
*/

/* Sample Output:

$ bf -c -t `cat hello_world.bf`
Hello World!
Contents of which cells to display?
	[1] First 'n' cells
	[2] Cells in an inclusive range
	[3] All cells
(Default [1]): 1
Enter value of 'n': 7
[0]  ->  0
[1]  ->  87
[2]  ->  100
[3]  ->  33
[4]  ->  10
[5]  ->  0
[6]  ->  0
*/
