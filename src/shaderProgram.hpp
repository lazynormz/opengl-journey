#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <glm/glm.hpp>

class ShaderProgram
{
public:
    ShaderProgram();  // Constructor
    ~ShaderProgram(); // Destructor

    void LoadShaders(const char *vertexPath, const char *fragmentPath); // Load shaders from files
    void Use();                                                         // Use the shader program
    void SetUniform(const char *name, float value);                     // Set uniform variable in shader
    void SetUniform(const char *name, int value);                       // Set uniform variable in shader
    void SetUniform(const char *name, const glm::mat4 &value);          // Set uniform variable in shader

    unsigned int m_programID; // Shader program ID
private:
};

#endif // __SHADER_PROGRAM_HPP__