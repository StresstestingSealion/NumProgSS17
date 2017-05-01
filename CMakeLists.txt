cmake_minimum_required(VERSION 3.7)
project(NumProgSS17)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -O3 -funroll-loops -march=native -mtune=native -std=c99")

add_executable(P1 S1/p1_lr.c)
add_executable(P2
        P2/p2_blaslr.c
        P2/basic.c P2/basic.h
        P2/matrix.c P2/matrix.h
        P2/miniblas.c P2/miniblas.h)