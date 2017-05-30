add_executable(P6 basic.c basic.h
        p6_triangulation.c
        surface3d.c surface3d.h)

target_link_libraries(P6 freeglut opengl32 glu32 winmm)