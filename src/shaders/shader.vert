#version 330 core

layout (location = 0) in vec3 aPos;    // Position (x, y, z)
layout (location = 1) in vec3 aColor;  // Color (r, g, b)

out vec3 vertexColor; // pass color to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // Just pass position straight to clip space
    vertexColor = aColor;          // Pass color to fragment shader
}