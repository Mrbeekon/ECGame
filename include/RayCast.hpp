#pragma once
#ifndef GAME_H
#define GAME_H

#include "ec.hpp"
#include "Graphics.hpp"

class RayCast
{
public:
    RayCast();
    ~RayCast();
    void Tick(TickAtt ta);
    void Render(Graphics*);
};

#endif
