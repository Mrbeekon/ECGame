#include "InputMan.h"

// TODO: Make keys into structs with a way of tracking cool down. Implement CHANGABLE controls.

void InputMan::SetKeyDown(SDLKey k)
{
    keys[k] = true;
}

void InputMan::SetKeyUp(SDLKey k)
{
    keys[k] = false;
}

bool InputMan::GetKey(SDLKey k)
{
    return keys[k];
}

void InputMan::ReleaseAll()
{
    for (int i = 0; i < SDLKEYCOUNT; i++)
        keys[i] = false;
}
