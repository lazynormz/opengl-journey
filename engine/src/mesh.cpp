#include <vector>
#include <glad/glad.h>
#include <tiny_gltf.h>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "tinyUtil.hpp"

namespace Graphics
{
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

        SetupMesh(); // Setup the mesh buffers
    }

    void Mesh::Draw()
    {
        glBindVertexArray(m_VAO);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_SHORT, 0);
    }

    void Mesh::SetupMesh()
    {
        std::vector<Vertex> vertices = Interlace();

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    std::vector<Vertex> Mesh::Interlace()
    {
        std::vector<Vertex> vertices;
        vertices.reserve(m_positions.size());

        for (size_t index = 0; index < m_positions.size(); ++index)
        {
            Vertex vertex;
            vertex.position = m_positions[index];
            vertex.normal = m_normals[index];
            vertex.uv = m_uvs[index];
            vertices.push_back(vertex);
        }

        return vertices;
    }
}