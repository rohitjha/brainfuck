bf: src/brainfuck.c src/brainfuck_shell.c
	gcc -O3 -o bf src/brainfuck.c src/brainfuck_shell.c

clean:
	rm -f bf
