#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "brainfuck.h"

/* Read the file and pass it to the bf_eval() function.
 * Update: Now this function read dynamic and filter the input.
 *         Return 1 on success, and 0 on error.
 */
int bf_readfile(char *filename) {
	size_t n = 0, sz = 4;
	char* chars = malloc(sz);
	if(chars == NULL) {
		perror("Can't allocate memory");
		return 0;
	}

	FILE* f = fopen(filename, "r");
	if(f == NULL) {
		free(chars);
		perror("Can't open file");
		return 0;
	}

	char c, *r = NULL;
	while((c = fgetc(f)) != EOF) {
		if((r = strchr("<>+-[].,", c))) {
			if(n == sz) {
				sz *= 2;
				void* t = realloc(chars, sz);
				if(t == NULL) {
					free(chars);
					fclose(f);
					perror("Error allocating memory");
					return 0;
				}
				chars = t;
			}
			chars[n++] = *r;
		}
	}
	fclose(f);

	bf_eval(chars);
	free(chars);

	return 1;
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
					exit(EXIT_SUCCESS);
				case 'f':
					if(!bf_readfile(optarg)) {
						exit(EXIT_FAILURE);
					}
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
						exit(EXIT_FAILURE);
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

		free(pipe);
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
