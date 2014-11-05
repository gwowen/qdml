#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vecmath.h"
#include "shaders2.h"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
      fprintf( stderr, "Failed to initialize GLFW\n");
      return -1;
    }

    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if ( window == NULL )
    {
      fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if( glewInit() != GLEW_OK ) {
      fprintf( stderr, "Failed to initialize GLEW\n" );
      return -1;
    }


    //nice dark blue background!
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f );

    GLuint vertexArrayID;
    glGenVertexArrays( 1, &vertexArrayID );
    glBindVertexArray( vertexArrayID );

    GLuint testProgram = LoadShader( "vertshader.glsl", "fragshader.glsl" );

    GLuint matrixID = glGetUniformLocation( testProgram, "MVP" );

    vecmath::mat4 Projection = vecmath::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );

    vecmath::mat4 View = vecmath::lookAt(
                          vecmath::vec3( 4.0f, 3.0f, 3.0f ),
                          vecmath::vec3( 0.0f, 0.0f, 0.0f ),
                          vecmath::vec3( 0.0f, 1.0f, 0.0f ) );

    //vecmath::mat4 Model = vecmath::scale( 1.0f );

    vecmath::mat4 Model = vecmath::mat4::identity();
	
    vecmath::mat4 MVP = Projection * View * Model;

    static const GLfloat vertexBufferData[] = {
      -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f, 1.0f, 0.0f };

    static const GLushort elementBufferData[] = { 0, 1, 2 };

    GLuint vertexBuffer;
    glGenBuffers( 1, &vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertexBufferData), vertexBufferData, GL_STATIC_DRAW );



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( testProgram );

        glUniformMatrix4fv( matrixID, 1, GL_FALSE, &MVP[0][0] );

        glEnableVertexAttribArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glDisableVertexAttribArray( 0 );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers( 1, &vertexBuffer );
    glDeleteProgram( testProgram );
    glDeleteVertexArrays( 1, &vertexArrayID );

    glfwTerminate();
    return 0;
}
