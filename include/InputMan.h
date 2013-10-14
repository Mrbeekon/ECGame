#pragma once
#include "stdafx.h"

#define SDLKEYCOUNT         SDLK_LAST   // The last entry in in the SDLkey enum, whose value will specify the enum size

class InputMan
{
public:
    void set_key_down(SDLKey k);          // Set the down status SDLKey, k, to true
    void set_key_up(SDLKey k);            // Set the down status SDLKey, k, to false
    bool get_key(SDLKey k);              // Returns the down status of SDLKey, k
    void release_all();                  // Set the down status of all keys to false
private:
    bool keys[SDLKEYCOUNT];
};
