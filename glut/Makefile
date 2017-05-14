

#
# Compiler settings
#
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Wextra -g
LIBS = -lm

#
# Compiler options for packages
#

GLUT = -lglut -lGLU -lGL
#win
#GLUT = -lfreeglut -lopengl32 -lglu32


#
# Tests
#
SOURCES_TESTS := \
	test_opengl1.c\
	test_opengl2.c

PROGRAMS_TESTS := $(SOURCES_TESTS:.c=)

#
# Build targets
#
all: $(PROGRAMS_TESTS)

clean:
	rm -f *.exe


#
# Build rule for test programs
#
$(PROGRAMS_TESTS): %: %.c
	$(CC) $(CFLAGS) $< $(LIBS) $(GLUT) -o $@
