#ifndef __MESH_HPP__
#define __MESH_HPP__

class Mesh
{
public:
    Mesh();  // Constructor
    ~Mesh(); // Destructor

    void LoadMesh(const char *path); // Load mesh from file
    void Draw();                     // Draw the mesh

private:                // Private Methods
private:                // Private members
    unsigned int m_VAO; // Vertex Array Object ID
    unsigned int m_VBO; // Vertex Buffer Object ID
    unsigned int m_EBO; // Element Buffer Object ID
};

#endif // __MESH_HPP__