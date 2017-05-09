cmake_minimum_required(VERSION 3.7)
project(NumProgSS17)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -O3 -funroll-loops -march=native -mtune=native -std=c99 -Wno-unknown-pragmas")

add_subdirectory(P1)
add_subdirectory(P2)
add_subdirectory(P3)