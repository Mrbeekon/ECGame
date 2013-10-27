#include "InputMan.hpp"

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
    for (int i = 0; i < SDLK_LAST; i++)
        keys[i] = false;
}
