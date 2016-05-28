#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "brainfuck.h"

/* Read the file and pass it to the bf_eval() function */
void bf_readfile(char *filename) {
	FILE *file;
	//int c;
	//int pointer = 0;
	uint32_t size = 0;

	/* Get the size of the file */	
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Error: Failed to open %s!\n", filename);
		exit(EXIT_FAILURE);
	}
	
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	/* Place each character from the file into the array */
	char* chars = NULL;
	chars = malloc((size + 1) * sizeof(*chars));
	if(!fread(chars, size, 1, file)) {
		fprintf(stderr, "Error: Unable to read %s\n", filename);
		exit(EXIT_FAILURE);
	}
	chars[size] = '\0';
	
	/* Close the file */
	fclose(file);

	/* Evaluate the code */
	bf_eval(chars);
}

int main(int argc, char *argv[]) {

	/* Ensure proper usage */
	if (argc < 2) {
		fprintf(stdout, USAGEMSG);
		return EXIT_FAILURE;
	}

	if(isatty(fileno(stdin))) {
		uint32_t  opt;
		uint32_t limit;

		while((opt = getopt(argc, argv, "hf:e:t:")) != -1) {
			switch(opt) {
				case 'h':
					fprintf(stdout, USAGEMSG);
					return EXIT_SUCCESS;
				case 'f':
					bf_readfile(optarg);
					break;
				case 'e':
					bf_eval(optarg);
					break;
				case 't':
					limit = atoi(optarg);
					if (limit <= MAX_CELLS) {
						bf_showtape_range(0, limit);
					}
					else {
						fprintf(stderr, "The number of tape memory locations to be displayed should be between 0 and 65535.\n");
						return EXIT_FAILURE;
					}
					break;
				case '?':
					fprintf(stdout, "Please type bf -h for help.\n");
					break;
			}
		}
	}

	/* Write operations to pipe and evaluate */
	else {
		/* tape memory of size MAX_CELLS*/
		char* pipe = NULL;
		pipe = (char*) malloc(MAX_CELLS * sizeof(char));

		if(!fgets(pipe, MAX_CELLS, stdin)) {
			fprintf(stderr, "Unable to read into tape\n");
		}
		bf_eval(pipe);
	}

	return EXIT_SUCCESS;
}


/* Sample Output:

$ bf -h
c-brainfuck, Version 0.5.1
Copyright (c) Rohit Jha, 2015

Usage: bf [options]
	-h		display this help message
	-f <file>	execute program in <file>
	-e <code>	evaluate brainfuck code in the <code> text
	-t <limit>	display tape memory upto <limit> cells
*/

/* Sample Output:

$ bf -f c-brainfuck/examples/hello_world.bf 
Hello World!
*/

/* Sample Output:

$ bf -e '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.'
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
