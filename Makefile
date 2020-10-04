CC = gcc
SOURCEDIR = src
BUILDDIR = build

.PHONY: context_switch.o test clean main

all: clean context_switch.o main

main: 
	gcc ${BUILDDIR}/context_switch.o ${SOURCEDIR}/context_switch.h ${SOURCEDIR}/main.c -o ${BUILDDIR}/main

context_switch.o:
	gcc -c ${SOURCEDIR}/context_switch.c -o ${BUILDDIR}/context_switch.o

test:
	${BUILDDIR}/main

clean:
	rm -f ${BUILDDIR}/*.o
	rm -f main
