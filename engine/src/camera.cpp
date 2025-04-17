#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <camera.hpp>

namespace Graphics
{
    Camera::Camera()
    {
        m_position = glm::vec3(0.0f, 0.0f, 3.0f); // Set initial camera position
        m_target = glm::vec3(0.0f, 0.0f, 0.0f);   // Set initial camera target
        m_up = glm::vec3(0.0f, 1.0f, 0.0f);       // Set initial up vector
        m_fov = 45.0f;                            // Set initial field of view
        m_aspectRatio = 16.0f / 9.0f;             // Set initial aspect ratio
        m_nearPlane = 0.1f;                       // Set initial near plane distance
        m_farPlane = 100.0f;                      // Set initial far plane distance
    }

    Camera::~Camera()
    {
        // Destructor implementation (if needed)
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(m_position, m_target, m_up); // Create view matrix using position, target, and up vector
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane); // Create projection matrix using FOV, aspect ratio, near and far planes
    }
}