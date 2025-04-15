#include <SDL3/SDL.h>
#include <SDL3/SDL_Video.h>
#include <glad/glad.h>
#include "game.hpp"
#include "shaderProgram.hpp"

#include "gameState.hpp"

unsigned int VBO, VAO;

Game::Game()
{
    Init();
}

Game::~Game()
{
    Cleanup();
}

void Game::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_window = SDL_CreateWindow("Hello SDL", 600, 600, SDL_WINDOW_OPENGL);
    if (m_window == nullptr)
    {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    m_glContext = SDL_GL_CreateContext(m_window);
    if (m_glContext == nullptr)
    {
        SDL_Log("SDL_GL_CreateContext Error: %s", SDL_GetError());
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_Log("Failed to initialize GLAD");
        SDL_GL_DestroyContext(m_glContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    m_running = true;
    m_shaderProgram = ShaderProgram();                                         // Initialize shader program
    m_shaderProgram.LoadShaders("shaders/shader.vert", "shaders/shader.frag"); // Load shaders
    m_shaderProgram.Use();                                                     // Use the shader program
}

void Game::Run()
{
    float testTri[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(testTri), testTri, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (m_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                m_running = false;
            }
        }
        GameState::DeltaTime = SDL_GetTicks() / 1000.0f; // Update delta time
        Update();
        Render();
    }

    Cleanup();
}

void Game::Update()
{
    // TODO: Update game state
    // For example, handle input, update game objects, etc.
}

void Game::Render()
{
    // TODO: Render game state
    // For example, clear the screen, draw game objects, etc.
    glClear(GL_COLOR_BUFFER_BIT);              // <--- YOU NEED THIS EVERY FRAME
    glUseProgram(m_shaderProgram.m_programID); // Use the shader program (replace 0 with your shader program ID)
    glBindVertexArray(VAO);                    // Bind the vertex array object (replace 0 with your VAO ID)
    glDrawArrays(GL_TRIANGLES, 0, 3);          // Draw the triangle (replace 0 and 3 with your vertex array and count)
    SDL_GL_SwapWindow(m_window);
}

void Game::Cleanup()
{
    SDL_GL_DestroyContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
