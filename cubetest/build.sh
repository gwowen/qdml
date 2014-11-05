clang++ `pkg-config --cflags glfw3` -o cubetest -g cubetest.cpp shaders2.cpp -lGLEW `pkg-config --static --libs glfw3` --std=c++11
