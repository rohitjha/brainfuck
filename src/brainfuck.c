#include <stdio.h>
#include <string.h>

#ifndef BRAINFUCK_H
#include "brainfuck.h"
#endif

int tape[MAX_CELLS];

/* Evaluate operators that are passed in the form of a character array */
void bf_eval(char *chars) {
	char c;
	int cell = 0;
	int char_pointer = 0;
	int loop = 0;

	/* Loop through all character in the character array */
	while (char_pointer < strlen(chars)) {
		switch (chars[char_pointer]) {
			
			/* Move the pointer to the right (next memory cell) */
			case '>':
				cell++;
				/* Circular tape */
				if (cell >= MAX_CELLS) {
					cell = cell % MAX_CELLS;
				}
				break;
			
			/* Move the pointer to the left (previous memory cell) */
			case '<':
				cell--;
				/* Circular tape */
				if (cell < 0) {
						while (cell < 0) {
							cell = cell + MAX_CELLS;
						}
					cell = cell % MAX_CELLS;
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

	if (a < 0 || b < 0 || a > b || a > MAX_CELLS || b > MAX_CELLS) {
		fprintf (stderr, "Error: invalid range(s)\nThe upper memory tape limit must be less than %d\n", MAX_CELLS);
	}

	else {
		for (i = a; i <= b; i++)
			printf ("[%d]  ->  %d\n", i, tape[i]);
	}
}
