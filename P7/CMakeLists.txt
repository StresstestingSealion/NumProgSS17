add_executable(P7 basic.c basic.h
        p7_interpolation.c
        interpolation.c interpolation.h)

target_link_libraries(P7 freeglut opengl32 glu32 winmm)