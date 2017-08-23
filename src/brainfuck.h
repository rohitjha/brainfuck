#include <stdint.h>

#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#define MAX_CELLS 65536
#define MAX_BUFFER 65536

/* Evaluating the brainfuck code passed as sequence of characters */
void bf_eval(char *);

/* Diplaying the specified number of tape entries */
void bf_showtape(uint32_t);

/* Displaying the contents of the tape elements specified by the range */
void bf_showtape_range(uint32_t, uint32_t);

#endif
