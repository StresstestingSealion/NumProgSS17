CC = gcc

CFLAGS = -Wall \
	 -O3 -funroll-loops -march=native -mtune=native \
         -std=c99
GLUT = -lglut -lGLU -lGL

all: p5_wave

basic.o: basic.c basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 
	
gridfunc1d.o: gridfunc1d.c gridfunc1d.h basic.h
	$(CC) -c $(CFLAGS) $< -o $@ 
	
leapfrog1d.o: leapfrog1d.c leapfrog1d.h basic.h gridfunc1d.h	
	$(CC) -c $(CFLAGS) $< -o $@ 	

p5_wave: p5_wave.o basic.o gridfunc1d.o leapfrog1d.o
	$(CC) $(CFLAGS) $^ -o $@ $(GLUT) -lm

p5_wave.o: p5_wave.c gridfunc1d.h leapfrog1d.h
	$(CC) $(CFLAGS) -c $< -o $@


