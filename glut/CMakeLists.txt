add_executable(glutTest1 test_opengl1.c)
add_executable(glutTest2 test_opengl2.c)

target_link_libraries(glutTest1 glu32 freeglut opengl32 m)
target_link_libraries(glutTest2 glu32 freeglut opengl32 m)