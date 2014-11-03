#include "shaders.h"

#include <GL/glew.h>
#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;

namespace shaders {
    GLuint testProg = 0;

map<GLenum, string> shaderTypeNames;

string readFile(const string &fileName) {
    ifstream stream( fileName );
    string str;

    std::cout << "Reading " << fileName << "\n";

    if( !stream ) {
        stringstream ss;
        ss << "Cannot open file: " << fileName;
        throw runtime_error( ss.str() );
    }

    stream.seekg( 0, ios::end );
    str.reserve( stream.tellg() );
    stream.seekg( 0, ios::beg );

    str.assign( ( istreambuf_iterator<char>(stream) ), istreambuf_iterator<char>() );
    return str;
}

GLuint createShader(GLenum shaderType, const string &shaderSource) {
    string shaderTypeName = shaderTypeNames[ shaderType ];

    GLuint shader = glCreateShader( shaderType );
    const char *shaderSourceData = shaderSource.data();

    GLint result;
    int logLength;

    glShaderSource( shader, 1, &shaderSourceData, NULL );
    glCompileShader( shader );

    glGetShaderiv( shader, GL_COMPILE_STATUS, &result );

    if( result == GL_FALSE ) {
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &result );
        std::vector<char> shaderError( logLength );
        glGetShaderInfoLog( shader, logLength, NULL, &shaderError[0] );
        std::cout << &shaderError[0] << "\n";
        //exit(1);
    }

    std::cout << "Shader compiled successfully!\n";

    return shader;
}

GLuint createProgram(const vector<GLuint> &shaders) {
    std::cout << "Linking program\n";
    GLuint program = glCreateProgram();

    for( auto shader : shaders )
        glAttachShader( program, shader );

    GLint result;
    GLint logLength;
    glGetProgramiv( program, GL_LINK_STATUS, &result);

    if( result == GL_FALSE ) {
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength );
        std::vector<char> programError( ( logLength > 1 ) ? logLength : 1);
        glGetProgramInfoLog( program, logLength, NULL, &programError[0] );
        std::cout << &programError[0] << "\n";
    }

    std::cout << "Program linked succesfully!\n";
    return program;
}

GLuint createProgram(string vertexShaderFilename, string fragmentShaderFilename) {
    vector<GLuint> shaders;
    string vertexShaderSource = readFile( vertexShaderFilename );
    string fragmentShaderSource = readFile( fragmentShaderFilename );
    shaders.push_back( createShader( GL_VERTEX_SHADER, vertexShaderSource ) );
    std::cout << "Vertex shader compiled successfully!\n";
    shaders.push_back( createShader( GL_FRAGMENT_SHADER, fragmentShaderSource ) );
    std::cout << "Fragment shader compiled successfully!\n";
    GLuint program = createProgram( shaders );
    for_each( shaders.begin(), shaders.end(), glDeleteShader );
    return program;
}


}
