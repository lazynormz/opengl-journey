#include <glad/glad.h>
#include <tiny_gltf.h>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "tinyUtil.hpp"

Mesh::Mesh()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::LoadMesh(const char *path)
{
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err, warn;

    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);

    if (!warn.empty())
    {
        printf("Warn: %s\n", warn.c_str());
    }

    if (!err.empty())
    {
        printf("Err: %s\n", err.c_str());
    }

    if (!ret)
    {
        printf("Failed to load glTF: %s\n", path);
        return;
    }

    const auto &mesh = model.meshes[0];         // Assuming we want the first mesh
    const auto &primitive = mesh.primitives[0]; // Assuming we want the first primitive

    tinygltf::ExtractVec3("POSITION", m_positions, model, primitive);
    tinygltf::ExtractVec3("NORMAL", m_normals, model, primitive);
    tinygltf::ExtractVec2("TEXCOORD_0", m_uvs, model, primitive);
    tinygltf::ExtractIndices(m_indices, model, primitive);
}

void Mesh::Draw()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    // Draw the mesh (not implemented in this example)
    // For example, you can use glDrawElements or glDrawArrays to render the mesh.
    // glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
