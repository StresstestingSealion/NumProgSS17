add_executable(P3
        p3_comparisonlr.c
        basic.c basic.h
        matrix.c matrix.h
        miniblas.c miniblas.h)

target_link_libraries(P3 winmm)