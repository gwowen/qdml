#include "shaders2.h"

//readFile - takes contents of a (shader) file and reads it into a string
//using ifstream

std::string readFile( const char* filePath ) {

  std::string content;
  std::ifstream fileStream( filePath, std::ios::in );

  if( !fileStream.is_open() ) {
    std::cerr << "Could not read file " << filePath << ". File does not exist\n";
    return "";
  }

  std::string line = "";
  while( !fileStream.eof() ) {
    std::getline( fileStream, line );
    content.append( line + "\n" );
  }

  fileStream.close();
  std::cout << filePath << " read!\n";
  return content;
}

//LoadShader - uses readFile to bring in shaders, checks them to ensure
//they've compiled properly and then returns a shader program
GLuint LoadShader( const char *vertex_path, const char *fragment_path ) {
  GLuint vertShader = glCreateShader( GL_VERTEX_SHADER );
  GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );

  std::string vertShaderStr = readFile( vertex_path );
  std::string fragShaderStr = readFile( fragment_path );
  const char *vertShaderSrc = vertShaderStr.c_str();
  const char *fragShaderSrc = fragShaderStr.c_str();

  GLint result = GL_FALSE;
  int logLength;

  //Compile the vertex shaders
  std::cout << "Compiling vertex shader\n";
  glShaderSource( vertShader, 1, &vertShaderSrc, NULL );
  glCompileShader( vertShader );

  //check to ensure the shader has compiled correctly using
  //glGetShaderiv

  glGetShaderiv( vertShader, GL_COMPILE_STATUS, &result );
  glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLength );
  std::vector<char> vertShaderError( logLength );
  glGetShaderInfoLog( vertShader, logLength, NULL, &vertShaderError[ 0 ] );
  std::cout << &vertShaderError[ 0 ] << "\n";

  //do the same for the fragment shader
  std::cout << "Compiling fragment shader\n";
  glShaderSource( fragShader, 1, &fragShaderSrc, NULL );
  glCompileShader( fragShader );

  glGetShaderiv( fragShader, GL_COMPILE_STATUS, &result );
  glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, & result );
  std::vector<char> fragShaderError( logLength );
  glGetShaderInfoLog( fragShader, logLength, NULL, &fragShaderError[ 0 ] );
  std::cout << &fragShaderError[ 0 ] << "\n";

  std::cout << "Linking program\n";
  GLuint program = glCreateProgram();
  glAttachShader( program, vertShader );
  glAttachShader( program, fragShader );
  glLinkProgram( program );

  glGetProgramiv( program, GL_LINK_STATUS, &result );
  glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength );
  std::vector<char> programError( ( logLength > 1 ) ? logLength : 1 );
  glGetProgramInfoLog( program, logLength, NULL, &programError[ 0 ] );
  std::cout << &programError[ 0 ] << "\n";

  glDeleteShader( vertShader );
  glDeleteShader( fragShader );

  return program;
}
