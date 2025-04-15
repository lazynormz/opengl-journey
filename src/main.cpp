#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "game.hpp"

int main(int argc, char *argv[])
{
    Game game;
    game.Run();
    return 0;
}