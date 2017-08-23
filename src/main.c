#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "brainfuck.h"

static int shlp = 0, sver = 0;

static struct option opts[] = {
	{"file",        required_argument, 0, 'f'},
	{"eval",        required_argument, 0, 'e'},
	{"interpreter", no_argument,       0, 'i'},
	{"filter",      required_argument, 0, 'F'},
	{"balance",     required_argument, 0, 'h'},
	{"help",        no_argument,   &shlp,  1 },
	{"version",     no_argument,   &sver,  1 },
	{0, 0, 0, 0}
};

char* bf_filter(FILE* f)
{
	size_t n = 0, cp = 4;
	char* out = malloc(cp);
	if(out == NULL) {
		perror("Can't allocate memory");
		return NULL;
	}

	char c, *r = NULL;

	while((c = fgetc(f)) != EOF) {
		if((r = strchr("<>+-[].,", c))) {
			if(n == cp) {
				cp *= 2;
				void* t = realloc(out, cp);
				if(t == NULL) {
					free(out);
					perror("Error allocating memory");
					return NULL;
				}
				out = t;
			}
			out[n++] = *r;
		}
	}

	if(n != cp) {
		void* t = realloc(out, n+1);
		if(t == NULL) {
			free(out);
			perror("Error allocating memory");
			return NULL;
		}
		out = t;
		out[n] = 0;
	}

	return out;
}

void showhelp(int);
void showversion(void);

int main(int argc, char *argv[]) {
	int c, i;
	char* code;
	FILE* f;

	while(1) {
		c = getopt_long(argc, argv, "if:e:F:b:", opts, &i);

		if(c == -1) break;

		if(shlp) {
			showhelp(EXIT_SUCCESS);
		}
		if(sver) {
			showversion();
		}

		switch(c) {
			case 'i':
				/* TODO: An interpreter... */
				break;
			case 'f':
				f = fopen(optarg, "r");
				if(f == NULL) {
					perror("Can't open file");
					exit(EXIT_FAILURE);
				}
				code = bf_filter(f);
				fclose(f);
				if(code == NULL) {
					exit(EXIT_FAILURE);
				}
				bf_eval(code);
				free(code);
				break;
			case 'e':
				bf_eval(optarg);
				break;
			case 'F':
				f = fopen(optarg, "r");
				if(f == NULL) {
					perror("Can't open file");
					exit(EXIT_FAILURE);
				}
				code = bf_filter(f);
				fclose(f);
				if(code == NULL) {
					exit(EXIT_FAILURE);
				}
				puts(code);
				free(code);
				break;
			case 'b':
				/* TODO: A function that balace brainfuck code... */
				break;
			case '?':
				showhelp(EXIT_FAILURE);
				break;
		}
	}

	if (optind < argc) {
    	while(optind < argc) {
    		f = fopen(argv[optind++], "r");
			if(f == NULL) {
				perror("Can't open file");
				exit(EXIT_FAILURE);
			}
			code = bf_filter(f);
			fclose(f);
			if(code == NULL) {
				exit(EXIT_FAILURE);
			}
			bf_eval(code);
			free(code);
			break;
    	}
    }

	return EXIT_SUCCESS;
}

void showhelp(int status)
{
	if(status != EXIT_SUCCESS) {
		fputs("Please type bf -h for help.\n", stderr);
	} else {
		fputs(
			"bf [options] FILENAME...\n\n"
			"Options:\n"
			"    -f --file <file>    Execute program in <file>\n"
			"    -e --eval <code>    Evaluate Brainfuck code in <code>\n"
			"    -i --interpreter    Branfuck interative interpreter (Unimplemented)\n"
			"    -F --filter <file>  Filter a file to only Brainfuck Characters\n"
			"    -b --balance <file> Balance '<', '>', '+' and '-' characters\n"
			"                        from <file> (Unimplemented)\n"
			"       --help           Show this help message and exit\n"
			"       --version        Show version info and exit\n\n", stdout);
	}

	exit(status);
}

void showversion(void)
{
	fputs(
		"c-brainfuck, Version 0.5.3\n"
		"Copyright (c) Rohit Jha, 2015-2017\n"
		"rohit305jha@gmail.com\n\n"
		"This is free and unencumbered software released into the public domain.\n\n"
		"Fork me on github https://github.com/rohitjha/brainfuck\n", stdout);
	exit(EXIT_SUCCESS);
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
