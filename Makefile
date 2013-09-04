# Select C compiler
CC=gcc

# Flags/options to pass to CC
CCFLAGS=-Wall -O3 -o

# C source files
CSRC=src/brainfuck.c src/c_brainfuck.c

# C header files
HEADERS=src/brainfuck.h

# Application's name
TGT=bf

# Where to install the executable/binary
TGT_LOC=/usr/bin


${TGT}: ${CSRC} ${HEADERS}
	${CC} ${CCFLAGS} ${TGT} ${CSRC}

clean:
	rm -f ${TGT}

install:
	cp ${TGT} ${TGT_LOC};
	chmod a+x ${TGT_LOC}/${TGT};
	chmod og-w ${TGT_LOC}/${TGT};
	rm -f ${TGT};

uninstall:
	rm -f ${TGT_LOC}/${TGT}
