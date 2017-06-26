add_executable(P8 basic.c basic.h
        p8_quadrature.c
        quadrature.c quadrature.h)

target_link_libraries(P8 freeglut opengl32 glu32 winmm)