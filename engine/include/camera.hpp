#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/glm.hpp>

namespace Graphics
{
    class Camera
    {
    public:
        Camera();  // Constructor
        ~Camera(); // Destructor

        glm::mat4 GetViewMatrix() const;       // Get the view matrix
        glm::mat4 GetProjectionMatrix() const; // Get the projection matrix
    public:                                    // Public members
    private:                                   // Private methods
    private:                                   // Private members
        glm::vec3 m_position;                  // Camera position
        glm::vec3 m_target;                    // Camera target
        glm::vec3 m_up;                        // Up vector
        float m_fov;                           // Field of view
        float m_aspectRatio;                   // Aspect ratio
        float m_nearPlane;                     // Near plane distance
        float m_farPlane;                      // Far plane distance
    };
}

#endif // __CAMERA_HPP__