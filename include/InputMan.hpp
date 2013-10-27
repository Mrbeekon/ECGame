#pragma once
#ifndef INPUTMAN_H
#define INPUTMAN_H

#include "ec.hpp"

class InputMan
{
public:
    // Set the down status SDLKey, k, to true
    void set_key_down(SDLKey k);

    // Set the down status SDLKey, k, to false
    void set_key_up(SDLKey k);

    // Returns the down status of SDLKey, k
    bool get_key(SDLKey k);

    // Set the down status of all keys to false
    void release_all();
    
    // Process input-related events from the SDL_Event
    void event_proc(SDL_Event e);
private:
    bool keys[SDLK_LAST];
};

#endif
