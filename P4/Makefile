CC = gcc

CFLAGS = -Wall -Werror \
	 -O3 -funroll-loops -march=native -mtune=native \
         -std=c99

all: p4_inverseiteration

basic.o: basic.c basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 

miniblas.o: miniblas.c miniblas.h basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 

matrix.o: matrix.c matrix.h miniblas.h
	$(CC) -c $(CFLAGS) $< -o $@ 

p4_inverseiteration: p4_inverseiteration.o basic.o miniblas.o matrix.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

p4_inverseiteration.o: p4_inverseiteration.c matrix.h miniblas.h
	$(CC) $(CFLAGS) -c $< -o $@


