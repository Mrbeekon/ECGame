#pragma once
#include "stdafx.h"

#define ENUMSIZE__SDLKEY    SDLK_LAST

class InMan
{
public:
    void SetKeyDown(SDLKey k);
    void SetKeyUp(SDLKey k);
    bool GetKey(SDLKey k);
private:
    bool keys[ENUMSIZE__SDLKEY];
};
