project(cubetest)
add_executable(cubetest src/cubetest.cpp src/shaders2.cpp)
target_link_libraries(cubetest ${GLFW_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})