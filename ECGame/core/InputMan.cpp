#include "InputMan.h"

// TODO: Make keys into structs with a way of tracking cool down. Implement CHANGABLE controls.

void InputMan::set_key_down(SDLKey k)
{
    keys[k] = true;
}

void InputMan::set_key_up(SDLKey k)
{
    keys[k] = false;
}

bool InputMan::get_key(SDLKey k)
{
    return keys[k];
}

void InputMan::release_all()
{
    for (int i = 0; i < SDLKEYCOUNT; i++)
        keys[i] = false;
}
