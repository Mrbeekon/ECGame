#pragma once
#include "stdafx.h"

#define SDLKEYCOUNT         SDLK_LAST   // The last entry in in the SDLkey enum, whose value will specify the enum size

class InputMan
{
public:
    void SetKeyDown(SDLKey k);          // Set the down status SDLKey, k, to true
    void SetKeyUp(SDLKey k);            // Set the down status SDLKey, k, to false
    bool GetKey(SDLKey k);              // Returns the down status of SDLKey, k
    void ReleaseAll();                  // Set the down status of all keys to false
private:
    bool keys[SDLKEYCOUNT];
};
