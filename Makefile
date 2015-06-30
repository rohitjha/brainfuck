# Select C compiler
CC=gcc

# Flags/options to pass to CC
CFLAGS=-Wall -O3 -o

# C source files
CSRC=src/brainfuck.c src/c_brainfuck.c

# C header files
HEADERS=src/brainfuck.h

# Application's name
TGT=bf

# Where to install the executable/binary
TGT_LOC=/usr/bin

# Man page source file
MAN_SRC=doc/bf.1

# GROFF-ed man page
G_MAN=bf.1

# Where to install the man page
MAN_LOC=/usr/share/man/man1

${TGT}: ${CSRC} ${HEADERS}
	${CC} ${CFLAGS} ${TGT} ${CSRC}

clean:
	rm -f ${TGT} ${G_MAN} ${G_MAN}.gz

install:
	cp ${TGT} ${TGT_LOC};
	chmod a+x ${TGT_LOC}/${TGT};
	chmod og-w ${TGT_LOC}/${TGT};
	rm -f ${TGT};
	groff -mandoc -T utf8 ${MAN_SRC} > ${G_MAN};
	gzip -c  ${G_MAN} > ${G_MAN}.gz
	cp ${G_MAN}.gz ${MAN_LOC}
	rm -f ${G_MAN} ${G_MAN}.gz

uninstall:
	rm -f ${TGT_LOC}/${TGT}
	rm -f ${MAN_LOC}/${G_MAN}.gz
