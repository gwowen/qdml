#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <string>
#include <vector>

using namespace std;


namespace shaders {
    extern GLuint testProg;

    string readFile( const string &fileName );
    GLuint createShader( GLenum shaderType, const string &shaderSource );
    GLuint createProgram( const vector<GLuint> &shaders );
    GLuint createProgram( string vertexShaderFilename, string fragementShaderFilename );
}

#endif // SHADERS_H
