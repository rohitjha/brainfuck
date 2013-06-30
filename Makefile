bf: src/brainfuck.c src/brainfuck.h src/brainfuck_shell.c
	gcc -O3 -o bf src/brainfuck.c src/brainfuck_shell.c

clean:
	rm -f bf

install:
	cp bf /usr/bin

deinstall:
	rm -f /usr/bin/bf
