CC = gcc

CFLAGS = -Wall -Werror \
	 -O3 -funroll-loops -march=native -mtune=native \
         -std=c99
GLUT = -lglut -lGLU -lGL

all: p8_quadrature

basic.o: basic.c basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 
	
quadrature.o: quadrature.c quadrature.h basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 

p8_quadrature: p8_quadrature.o basic.o quadrature.o
	$(CC) $(CFLAGS) $^ -o $@ $(GLUT) -lm

p8_quadrature.o: p8_quadrature.c quadrature.h 
	$(CC) $(CFLAGS) -c $< -o $@


