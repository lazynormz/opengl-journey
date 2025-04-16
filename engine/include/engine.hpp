#ifndef __GAME_CPP__
#define __GAME_CPP__

#include <vector>
#include <SDL3/SDL.h>
#include "shaderProgram.hpp"
#include "mesh.hpp"

namespace Engine
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
        ShaderProgram m_shaderProgram; // Shader program instance

        std::vector<Mesh> m_meshes; // Vector of meshes
    };
}

#endif // __GAME_CPP__