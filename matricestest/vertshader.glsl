#version 330 core

//input vertex data, different for all executions of the shader
layout( location = 0 ) in vec3 vertexPos_modelspace;

//values that stay constant for the whole mesh
uniform mat4 MVP;

void main() {
  gl_Position = MVP * vec4( vertexPos_modelspace, 1 );
}
