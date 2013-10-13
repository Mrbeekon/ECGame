#include "InputMan.h"

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
