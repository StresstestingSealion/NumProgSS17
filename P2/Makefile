CC = gcc

CFLAGS = -Wall -Werror \
	 -O1 -funroll-loops -march=native -mtune=native \
         -std=c99

all: p2_blaslr

basic.o: basic.c basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 

miniblas.o: miniblas.c miniblas.h basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 

matrix.o: matrix.c matrix.h miniblas.h
	$(CC) -c $(CFLAGS) $< -o $@ 

p2_blaslr: p2_blaslr.o basic.o miniblas.o matrix.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

p2_blaslr.o: p2_blaslr.c matrix.h
	$(CC) $(CFLAGS) -c $< -o $@


