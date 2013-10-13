#include "InMan.h"

void InMan::SetKeyDown(SDLKey k)
{
    keys[k] = true;
}

void InMan::SetKeyUp(SDLKey k)
{
    keys[k] = false;
}

bool InMan::GetKey(SDLKey k)
{
    return keys[k];
}
