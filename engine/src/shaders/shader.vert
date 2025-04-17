#version 330 core

layout (location = 0) in vec3 aPos;    // Position (x, y, z)
layout (location = 1) in vec3 aNormal;  // Normal (r, g, b)
layout (location = 2) in vec2 aUV;   // Uv (u, v)

uniform mat4 u_MVP; // Model matrix

out vec3 vertexColor; // pass color to fragment shader

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0); // Just pass position straight to clip space
    vertexColor = vec3(aPos);          // Pass color to fragment shader
}