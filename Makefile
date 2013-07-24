CC=gcc
CCFLAGS=-O2
SRC=src/brainfuck.c src/brainfuck.h src/c_brainfuck.c
CSRC=src/brainfuck.c src/c_brainfuck.c
TGT=bf
TGT_LOC=/usr/bin
TGT_PATH=/usr/bin/bf

${TGT}: ${SRC}
	${CC} ${CCFLAGS} -o ${TGT} ${CSRC}

clean:
	rm -f ${TGT}

install:
	cp ${TGT} ${TGT_LOC}

deinstall:
	rm -f ${TGT_PATH}
