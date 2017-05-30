CC = gcc

CFLAGS = -Wall -Werror \
	 -O3 -funroll-loops -march=native -mtune=native \
         -std=c99
GLUT = -lglut -lGLU -lGL

all: p6_triangulation


basic.o: basic.c basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 
	
surface3d.o: surface3d.c surface3d.h basic.h	
	$(CC) -c $(CFLAGS) $< -o $@ 

p6_triangulation: p6_triangulation.o basic.o surface3d.o
	$(CC) $(CFLAGS) $^ -o $@ $(GLUT) -lm

p6_triangulation.o: p6_triangulation.c basic.h surface3d.h 
	$(CC) $(CFLAGS) -c $< -o $@


