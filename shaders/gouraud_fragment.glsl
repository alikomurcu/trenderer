#version 330 core
out vec4 FragColor;
  
in vec3 Result;

void main()
{
    FragColor = vec4(Result, 1.0);
}