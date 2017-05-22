add_executable(P5 p5_wave.c
        leapfrog1d.c leapfrog1d.h
        gridfunc1d.c gridfunc1d.h
        basic.c basic.h)

target_link_libraries(P5 freeglut opengl32 glu32 winmm)