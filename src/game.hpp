#ifndef __GAME_CPP__
#define __GAME_CPP__

#include <SDL3/SDL.h>
#include "shaderProgram.hpp"

class Game
{
public:
    Game();  // Constructor
    ~Game(); // Destructor

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
};

#endif // __GAME_CPP__