#include <stdio.h>
#include <string.h>

#ifndef BRAINFUCK_H
#include "brainfuck.h"
#endif

int tape[MAX_CELLS];

/* Evaluate operators that are passed in the form of a character array */
void bf_eval(char *chars) {
	char c;
	uint32_t cell = 0;
	uint32_t char_pointer = 0;
	uint32_t loop = 0;

	uint32_t size = strlen(chars);

	/* Loop through all character in the character array */
	while (char_pointer < size) {
		switch (chars[char_pointer]) {
			
			/* Move the pointer to the right (next memory cell) */
			case '>':
				if (cell < MAX_CELLS - 1) {
					cell++;
				}
				else if (cell == MAX_CELLS - 1) {
					cell = 0;
				}
				break;
			
			/* Move the pointer to the left (previous memory cell) */
			case '<':
				if (cell == 0) {
					cell = MAX_CELLS - 1;
				}
				else {
					cell--;
				}
				break;
			
			/* Increment the memory cell under the pointer */
			case '+':
				tape[cell]++;
				break;
			
			/* Decrement the memory cell under the pointer */
			case '-':
				tape[cell]--;
				break;
			
			/* Output the character signified by the current memory cell */
			case '.':
				putchar(tape[cell]);
				break;
			
			/* Input a character and store it in the current memory cell */
			case ',':
				tape[cell] = (int) getchar();
				break;
			
			/* Jump past the matching ']' if the memory cell under the pointer holds 0 */
			case '[':
				if (tape[cell] == 0) {
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
			
			/* Jump back to the matching '[' if the memory cell under the pointer holds a nonzero value */
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
void bf_showtape(uint32_t n) {
	int i;
	int limit;

	if (n > MAX_CELLS)
		limit = MAX_CELLS;
	else
		limit = n;

	printf ("\nTape Contents:\n");

	for (i = 0; i < limit; i++)
			printf ("[%d]\t-> %d\n", i, tape[i]);
}

/* Display contents of tape cell numbers ranging from 'a' to 'b' */
void bf_showtape_range(uint32_t a, uint32_t b) {
	int i;

	if (a > b || a > MAX_CELLS || b > MAX_CELLS) {
		fprintf (stderr, "Error: invalid range(s)\nThe upper memory tape limit must be less than %d\n", MAX_CELLS);
	}

	else {
		printf ("\nTape Contents:\n");

		for (i = a; i <= b; i++)
			printf ("[%d]  ->  %d\n", i, tape[i]);
	}
}
