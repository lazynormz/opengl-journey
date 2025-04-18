#include <memory>
#include <engine.hpp>

class Box : public Actor::GameObject
{
public:
    Box() : Actor::GameObject("") {};

    Box(const char *modelPath) : Actor::GameObject(modelPath)
    {
    }

    void Update() override
    {
        // Update logic for the box
    }

    void Render() override
    {
        m_mesh.Draw();
    }
};

int main(int argc, char *argv[])
{
    Core::Engine engine; // Create an instance of the Engine class
    Box b("D:/cpp/fluid go swish/test_elements/cube.gltf");
    engine.RegisterGameObject(std::make_shared<Box>(b)); // Register the box game object
    engine.Run();                                        // Run the game loop
    return 0;                                            // Return success
}