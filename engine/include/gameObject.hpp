#ifndef __GAMEOBJECT_HPP__
#define __GAMEOBJECT_HPP__

#include <mesh.hpp>

namespace Actor
{
    class GameObject
    {
    public:
        GameObject(const char *modelPath)
        {
            if (modelPath == nullptr || modelPath == "")
            {
                return;
            }

            m_mesh.LoadMesh(modelPath); // Load the mesh from the specified path
        };
        virtual void Update() = 0; // Update the game object state
        virtual void Render() = 0; // Render the game object
    protected:
        // Private members for game object properties
        float m_position[3];   // Position of the game object (x, y, z)
        float m_rotation[3];   // Rotation of the game object (pitch, yaw, roll)
        float m_scale[3];      // Scale of the game object (x, y, z)
        Graphics::Mesh m_mesh; // Mesh associated with the game object
    };
}

#endif // __GAMEOBJECT_HPP__