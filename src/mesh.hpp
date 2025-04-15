#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>

class Mesh
{
public:
    Mesh();  // Constructor
    ~Mesh(); // Destructor

    void LoadMesh(const char *path); // Load mesh from file
    void Draw();                     // Draw the mesh

private:                                 // Private Methods
private:                                 // Private members
    std::vector<float> m_vertices;       // Vertex data
    std::vector<float> m_normals;        // Normal data
    std::vector<float> m_texCoords;      // Texture coordinate data
    std::vector<unsigned int> m_indices; // Index data

    unsigned int m_VAO; // Vertex Array Object ID
    unsigned int m_VBO; // Vertex Buffer Object ID
    unsigned int m_EBO; // Element Buffer Object ID
};

#endif // __MESH_HPP__