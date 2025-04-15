#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <SDL3/SDL_log.h>
#include "shaderProgram.hpp"

ShaderProgram::ShaderProgram()
{
    // Constructor implementation
}

ShaderProgram::~ShaderProgram()
{
    // Destructor implementation
}

void ShaderProgram::LoadShaders(const char *vertexPath, const char *fragmentPath)
{
    std::filesystem::path vertexFilePath(vertexPath);
    std::filesystem::path fragmentFilePath(fragmentPath);

    if (!std::filesystem::exists(vertexFilePath) || !std::filesystem::exists(fragmentFilePath))
    {
        // Handle error: file not found
        SDL_Log("Shader file not found: %s or %s", vertexPath, fragmentPath);
        return;
    }

    // Load shaders from files
    std::ifstream vertexFile(vertexFilePath);
    std::ifstream fragmentFile(fragmentFilePath);
    if (!vertexFile.is_open() || !fragmentFile.is_open())
    {
        return;
    }
    std::string vertexCode((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
    std::string fragmentCode((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());

    vertexFile.close();
    fragmentFile.close();

    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        // Handle shader compilation error
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        // Handle shader compilation error
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        // Handle program linking error
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    m_programID = shaderProgram; // Uncomment this line if you have a member variable to store the program ID
}

void ShaderProgram::Use()
{
    // Use the shader program
    glUseProgram(m_programID);
    // Set any default uniforms here if needed

    // Example: SetUniform("someUniform", 1.0f);
    // SetUniform("anotherUniform", 42);
    // SetUniform("textureSampler", 0); // For texture samplers, set the texture unit
}

void ShaderProgram::SetUniform(const char *name, float value)
{
    // Set uniform variable in shader
    int location = glGetUniformLocation(m_programID, name);
    if (location != -1)
    {
        glUniform1f(location, value);
    }
    else
    {
        // Handle error: uniform not found
    }
}

void ShaderProgram::SetUniform(const char *name, int value)
{
    // Set uniform variable in shader
    int location = glGetUniformLocation(m_programID, name);
    if (location != -1)
    {
        glUniform1i(location, value);
    }
    else
    {
        // Handle error: uniform not found
    }
}