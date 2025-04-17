#ifndef __GAME_CPP__
#define __GAME_CPP__

#include <vector>
#include <SDL3/SDL.h>
#include <camera.hpp>
#include "shaderProgram.hpp"
#include "mesh.hpp"

namespace Core
{
    class Engine
    {
    public:
        Engine();  // Constructor
        ~Engine(); // Destructor

        void Run();     // Main game loop
    private:            // Methods
        void Init();    // Initialize game
        void Update();  // Update game state
        void Render();  // Render game state
        void Cleanup(); // Cleanup resources

    private: // Properties
        SDL_Window *m_window;
        SDL_GLContext m_glContext;
        bool m_running;
        Graphics::ShaderProgram m_shaderProgram; // Shader program instance
        Graphics::Camera m_camera;               // Camera instance
        std::vector<Graphics::Mesh> m_meshes;    // Vector of meshes
    };
}

#endif // __GAME_CPP__