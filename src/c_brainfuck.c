#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "brainfuck.h"

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
	char pipe[MAX_CELLS];	/* tape memory of size MAX_CELLS*/

	/* Ensure proper usage */
	if (argc < 2) {
		printf(USAGEMSG);
		return EXIT_FAILURE;
	}

	if(isatty(fileno(stdin))) {
		int opt;
		int limit;
			
		while((opt = getopt(argc, argv, "hf:c:t:")) != -1) {
			switch(opt) {
				case 'h':
					printf(USAGEMSG);
					return EXIT_SUCCESS;
				case 'f':
					bf_readfile(optarg);
					break;
				case 'c':
					bf_eval(optarg);
					break;
				case 't':
					limit = atoi(optarg);
					if (limit >= 0) {
						bf_showtape_range(0, limit);
					}
					else {
						fprintf(stderr, "The number of tape memory locations to be displayed should be less than 65536.\n");
						return EXIT_FAILURE;
					}
					break;
				case '?':
					printf("Please type bf -h for help.\n");
					break;
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

$ bf -h
c-brainfuck, Version 0.5
Copyright (c) Rohit Jha, 2015

Usage: bf [options]
	-h		display this help message
	-f <file>	execute program in <file>
	-c <code>	run brainfuck code in the <code> text
	-t <limit>	display tape memory upto <limit> cells
*/

/* Sample Output:

$ bf -f c-brainfuck/examples/hello_world.bf 
Hello World!
*/

/* Sample Output:

$ bf -c '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.'
Hello World!
*/

/* Sample Output:

$ bf -f c-brainfuck/examples/hello_world.bf -t 9
Hello World!
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
