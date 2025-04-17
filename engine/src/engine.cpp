#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <SDL3/SDL.h>
#include <SDL3/SDL_Video.h>
#include <glad/glad.h>
#include "engine.hpp"
#include "shaderProgram.hpp"
#include "mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gameState.hpp"

namespace Core
{
    Engine::Engine()
    {
        Init();
    }

    Engine::~Engine()
    {
        Cleanup();
    }

    void Engine::Init()
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

        glEnable(GL_DEPTH_TEST); // Enable depth testing
        glEnable(GL_CULL_FACE);  // Enable backface culling

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set clear color
        glViewport(0, 0, 600, 600);           // Set viewport

        m_running = true;
        m_shaderProgram = Graphics::ShaderProgram();                               // Initialize shader program
        m_shaderProgram.LoadShaders("shaders/shader.vert", "shaders/shader.frag"); // Load shaders
        m_shaderProgram.Use();                                                     // Use the shader program
    }

    void Engine::Run()
    {
        Graphics::Mesh mesh;
        mesh.LoadMesh("D:\\cpp\\fluid go swish\\test_elements\\cube.gltf"); // Load your model here
        m_meshes.push_back(mesh);                                           // Add the mesh to the vector
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
            Global::GameState::DeltaTime = SDL_GetTicks() / 1000.0f; // Update delta time
            Update();
            Render();
        }

        Cleanup();
    }

    void Engine::Update()
    {
        // TODO: Update game state
        // For example, handle input, update game objects, etc.
    }

    void Engine::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // <--- YOU NEED THIS EVERY FRAME
        m_shaderProgram.Use();
        glm::mat4 model = glm::mat4(1.0f);                                                                                   // Identity matrix for model
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Camera view matrix
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);                                    // Perspective projection matrix
        m_shaderProgram.SetUniform("u_MVP", projection * view * model);                                                      // Set the MVP matrix uniform in the shader
        for (auto &mesh : m_meshes)
        {
            mesh.Draw(); // Draw the mesh
        }
        SDL_GL_SwapWindow(m_window);
    }

    void Engine::Cleanup()
    {
        SDL_GL_DestroyContext(m_glContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
}