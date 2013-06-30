bf: src/brainfuck.c src/brainfuck.h src/c_brainfuck.c
	gcc -O3 -o bf src/brainfuck.c src/c_brainfuck.c

clean:
	rm -f bf

install:
	cp bf /usr/bin

deinstall:
	rm -f /usr/bin/bf
