add_executable(P10 basic.c basic.h
        crs.h crs.c
        matrix.h matrix.c
        miniblas.h miniblas.c
        p10_crs.c)

target_link_libraries(P10 winmm)