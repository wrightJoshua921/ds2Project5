CFLAGS = -g -Wall 
CC = gcc

objects = matrices.o matrixDetail.o stack.o

test: $(objects)
	$(CC) -o optimal $(objects)

matrices.o: matrices.c stack.h matrixDetail.h matrices.h
matrixDetail.o: matrixDetail.c matrixDetail.h
stack.o: stack.c stack.h matrixDetail.h

.PHONY : clean
clean: 
	rm optimal $(objects)
