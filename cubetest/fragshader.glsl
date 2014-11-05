#version 330 core

//interpolated value from vertex shaders
in vec3 fragmentColor;

//output data
out vec3 color;

void main() {
  //output color red
  color = fragmentColor;
}
