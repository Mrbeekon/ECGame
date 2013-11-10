#ifndef GAME_H
#define GAME_H

#include "ec.hpp"
#include "InputMan.hpp"
#include "Random.hpp"
#include "Graphics.hpp"

class Game
{
public:
    InputMan* in;
    Random* rand;
    Game();
    ~Game();
    void start();
    void stop();
private:
    int width, height;
    unsigned long long uptime;
    bool running;
    SDL_Surface* surface;
    Bitmap* screen;
    void _render(Graphics* g);
    void _tick(TickAtt ta);
    void _run();
};

#endif
