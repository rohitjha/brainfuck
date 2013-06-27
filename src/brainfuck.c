#include <stdio.h>
#include <string.h>

#ifndef BRAINFUCK_H
	#include "brainfuck.h"
#endif

int tape[MAX_CELLS];

/* Evaluate operators that are passed in the form of a character array */
void bf_eval(char *chars) {
	char c;
	int pointer = 0;
	int char_pointer = 0;
	int loop = 0;

	/* Loop through all character in the character array */
	while (char_pointer < strlen(chars)) {
		switch (chars[char_pointer]) {
			/* Move the pointer to the right */
			case '>':
				pointer++;
				break;
			/* Move the pointer to the left */
			case '<':
				pointer--;
				break;
			/* Increment the memory cell under the pointer */
			case '+':
				tape[pointer]++;
				break;
			/* Decrement the memory cell under the pointer */
			case '-':
				tape[pointer]--;
				break;
			/* Output the character signified by the cell at the pointer */
			case '.':
				putchar(tape[pointer]);
				break;
			/* Input a character and store it in the cell at the pointer */
			case ',':
				tape[pointer] = (int) getchar();
				break;
			/* Jump past the matching ']' if the cell under the pointer is 0 */
			case '[':
				if (tape[pointer] == 0) {
					loop = 1;
					while (loop > 0) {
						c = chars[++char_pointer];
						if (c == '[')
							loop++;
						else if (c == ']')
							loop--;
					}
				}
				break;
			/* Jump back to the matching '[' if the cell under the pointer is nonzero */
			case ']':
				loop = 1;
				while (loop > 0) {
					c = chars[--char_pointer];
					if (c == '[')
						loop--;
					else if (c == ']')
						loop++;
				}
				char_pointer--;
				break;
		}
		char_pointer++;
	}
}

/* Display contents of the first 'n' cells of the tape */
void bf_showtape(int n) {
	int i;
	int limit;

	if (n < 0 || n > MAX_CELLS)
		limit = MAX_CELLS;
	else
		limit = n;

	for (i = 0; i < limit; i++)
			printf ("[%d]  ->  %d\n", i, tape[i]);
}

/* Display contents of tape cell numbers ranging from 'a' to 'b' */
void bf_showtape_range(int a, int b) {
	int i;
	int low;
	int high;

	if (a < 0 || b < 0 || a > b || a > MAX_CELLS || b > MAX_CELLS) {
		printf ("error: invalid range(s)\nLower limit must be non-negative and upper limit must be less than %d\n", MAX_CELLS);
	}

	else {
		for (i = a; i <= b; i++)
			printf ("[%d]  ->  %d\n", i, tape[i]);
	}
}
