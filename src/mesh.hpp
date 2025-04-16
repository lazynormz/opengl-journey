#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position; // Vertex position
    glm::vec3 normal;   // Vertex normal
    glm::vec2 uv;       // Texture coordinates
};

class Mesh
{
public:
    Mesh();  // Constructor
    ~Mesh(); // Destructor

    void LoadMesh(const char *path); // Load mesh from file
    void Draw();                     // Draw the mesh

private:                                // Private Methods
    std::vector<Vertex> Interlace();    // Interlace vertex data for GPU
    void SetupMesh();                   // Setup the mesh buffers
private:                                // Private members
    std::vector<glm::vec3> m_positions; // Vertex data
    std::vector<glm::vec3> m_normals;   // Normal data
    std::vector<glm::vec2> m_uvs;       // Texture coordinate data
    std::vector<uint16_t> m_indices;    // Index data

    unsigned int m_VAO; // Vertex Array Object ID
    unsigned int m_VBO; // Vertex Buffer Object ID
    unsigned int m_EBO; // Element Buffer Object ID
};

#endif // __MESH_HPP__