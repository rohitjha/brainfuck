CC=gcc
CCFLAGS=-O3 -o
#SRC=src/brainfuck.c src/brainfuck.h src/c_brainfuck.c
CSRC=src/brainfuck.c src/c_brainfuck.c
HEADERS=src/brainfuck.h
TGT=bf
TGT_LOC=/usr/bin
TGT_PATH=/usr/bin/bf

${TGT}: ${CSRC} ${HEADERS}
	${CC} ${CCFLAGS} ${TGT} ${CSRC}

clean:
	rm -f ${TGT}

install:
	cp ${TGT} ${TGT_LOC}

uninstall:
	rm -f ${TGT_PATH}
