add_executable(P9 basic.c basic.h
        p9_adaptive.c
        quadrature.c quadrature.h)

target_link_libraries(P9 freeglut opengl32 glu32 winmm)