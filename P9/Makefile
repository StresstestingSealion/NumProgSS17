CC = gcc

CFLAGS = -Wall -Werror \
	 -O3 -funroll-loops -march=native -mtune=native \
         -std=c99

all: p9_adaptive

basic.o: basic.c basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 
	
quadrature.o: quadrature.c quadrature.h basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 

p9_adaptive: p9_adaptive.o basic.o quadrature.o
	$(CC) $^ -o $@ -lm

p9_adaptive.o: p9_adaptive.c quadrature.h 
	$(CC) $(CFLAGS) -c $< -o $@


