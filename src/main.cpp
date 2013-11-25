#include "Game.hpp"

int main(int argc, char** argv)
{
    Game* game = new Game();
    InstanceMan::run(game);
    return EXIT_SUCCESS;
}