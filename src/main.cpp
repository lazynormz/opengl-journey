#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "game.hpp"
#include "mesh.hpp"

int main(int argc, char *argv[])
{
    Game game;

    Mesh mesh;
    mesh.LoadMesh("D:\\cpp\\fluid go swish\\test_elements\\cube.gltf"); // Load your model here

    game.Run();
    return 0;
}