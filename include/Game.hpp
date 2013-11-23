#ifndef GAME_H
#define GAME_H

#include "ECStd.hpp"
#include "InputMan.hpp"
#include "Random.hpp"
#include "Graphics.hpp"

class Game
{
public:
    const int FPS = 60;
    InputMan* in;
    Random* rand;
    Game();
    ~Game();
    void start();
    void stop();
private:
    uint width, height;
    bool running;
    SDL_Surface* surface;
    Bitmap* screen;
    void _render(Graphics* g);
    void _tick();
    void _run();
};

#endif
