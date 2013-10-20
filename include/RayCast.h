#pragma once
#ifndef GAME_H
#define GAME_H

#include "ec.h"
#include "Graphics.h"

class RayCast
{
public:
    RayCast();
    ~RayCast();
    void Tick(TickAtt ta);
    void Render(Graphics*);
};

#endif
