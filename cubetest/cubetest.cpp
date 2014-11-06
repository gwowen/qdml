#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "qdml.h"
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

    //enable depth testing and stop showing
    //depth values lesser than the ones already
    //being shown
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );

    GLuint vertexArrayID;
    glGenVertexArrays( 1, &vertexArrayID );
    glBindVertexArray( vertexArrayID );

    GLuint testProgram = LoadShader( "vertshader.glsl", "fragshader.glsl" );

    GLuint matrixID = glGetUniformLocation( testProgram, "MVP" );

    qdml::mat4 Projection = qdml::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );

    qdml::mat4 View = qdml::lookAt(
                          qdml::vec3( 4.0f, 3.0f, -3.0f ), //camera at (4,3,-3) in world space
                          qdml::vec3( 0.0f, 0.0f, 0.0f ), //looking at origin
                          qdml::vec3( 0.0f, 1.0f, 0.0f ) ); //head is up (set 0, -1, 0 to look upside down)

    qdml::mat4 Model = qdml::mat4::identity();

    qdml::mat4 MVP = Projection * View * Model;

    static const GLfloat vertexBufferData[] = {
    -1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f };

    static const GLfloat colorBufferData[] = {
      0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
    };

    GLuint vertexBuffer;
    glGenBuffers( 1, &vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertexBufferData), vertexBufferData, GL_STATIC_DRAW );

    GLuint colorBuffer;
    glGenBuffers( 1, &colorBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, colorBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW );




    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glUseProgram( testProgram );

        glUniformMatrix4fv( matrixID, 1, GL_FALSE, &MVP[0][0] );

        //attribute buffer for vertices
        glEnableVertexAttribArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

        //attribute buffer for colors
        glEnableVertexAttribArray( 1 );
        glBindBuffer( GL_ARRAY_BUFFER, colorBuffer );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

        glDrawArrays( GL_TRIANGLES, 0, 12*3 );

        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers( 1, &vertexBuffer );
    glDeleteBuffers( 1, &colorBuffer );
    glDeleteProgram( testProgram );
    glDeleteVertexArrays( 1, &vertexArrayID );

    glfwTerminate();
    return 0;
}
