add_executable(P2
        p2_blaslr.c
        basic.c basic.h
        matrix.c matrix.h
        miniblas.c miniblas.h)

target_link_libraries(P2 winmm)