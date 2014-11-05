//shaders.h - a shader loading function header file
#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

std::string readFile( const char* filePath );
GLuint LoadShader( const char *vertex_path, const char *fragment_path );

#endif
