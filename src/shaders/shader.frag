#version 330 core

in vec3 vertexColor; // color passed from vertex shader
out vec4 FragColor;  // output color

void main()
{
    FragColor = vec4(vertexColor, 1.0); // Use passed color, full alpha
}