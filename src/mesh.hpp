#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh();  // Constructor
    ~Mesh(); // Destructor

    void LoadMesh(const char *path); // Load mesh from file
    void Draw();                     // Draw the mesh

private:                                 // Private Methods
private:                                 // Private members
    std::vector<glm::vec3> m_positions;  // Vertex data
    std::vector<glm::vec3> m_normals;    // Normal data
    std::vector<glm::vec2> m_uvs;        // Texture coordinate data
    std::vector<unsigned int> m_indices; // Index data

    unsigned int m_VAO; // Vertex Array Object ID
    unsigned int m_VBO; // Vertex Buffer Object ID
    unsigned int m_EBO; // Element Buffer Object ID
};

#endif // __MESH_HPP__