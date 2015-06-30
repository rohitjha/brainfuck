#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#define MAX_CELLS 65536

#define USAGEMSG "c-brainfuck, Version 0.5.1\nCopyright (c) Rohit Jha, 2015\n\nUsage: bf [options]\n\t-h\t\tdisplay this help message\n\t-f <file>\texecute program in <file>\n\t-e <code>\tevaluate brainfuck code in the <code> text\n\t-t <limit>\tdisplay tape memory upto <limit> cells\n"

/* Evaluating the brainfuck code passed as sequence of characters */
void bf_eval(char *);

/* Diplaying the specified number of tape entries */
void bf_showtape(int);

/* Displaying the contents of the tape elements specified by the range */
void bf_showtape_range(int, int);

#endif
