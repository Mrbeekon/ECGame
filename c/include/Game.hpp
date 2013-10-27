#pragma once
#ifndef GAME_H
#define GAME_H

#include "ec.hpp"
#include "InputMan.hpp"
#include "Random.hpp"
#include "Graphics.hpp"

class Game
{
public:
    InputMan*       in;
    Random*         rnd;
    Game();
    ~Game();
    void Start();
    void Stop();
private:
    int width, height;
    bool running;
    SDL_Surface*    surface;
    Bitmap*         screen;
    void Render(Graphics* g);
    void Tick(TickAtt ta);
    void Run();
};

#endif
