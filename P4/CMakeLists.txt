add_executable(P4
        miniblas.c miniblas.h
        matrix.c matrix.h
        basic.c basic.h)

target_link_libraries(P4 m winmm)