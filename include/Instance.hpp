#ifndef INSTANCE_H
#define INSTANCE_H

#include "ECStd.hpp"
#include "Graphics.hpp"
#include "InputMan.hpp"

class Instance
{
    bool _running;
public: 
    const uint WIDTH = 1024, 
               HEIGHT = 768;

    SDL_Surface* surface;

    InputMan* in;
    Bitmap* screen;

    Instance();
    virtual ~Instance();

    // Call this to stop the main loop
    void stop(void);

    // The main run loop - unmodifiable by inheritors
    // Call to start
    bool run(void);

    /* Abstract Methods (Must be implemented) */

    // Called when the main loop startd
    virtual bool on_start(void) = 0;

    // Called on stop
    virtual void on_stop(void) = 0;

    // Called by the main loop. ALL RENDERING SHOULD BE DONE HERE.
    virtual void render(Graphics* g) = 0;

    // Called by the main loop. Use to 'tick' components (eg entities, level)
    virtual void tick(void) = 0;
};

#endif
