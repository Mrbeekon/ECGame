#ifndef ENGINEINSTANCE_H
#define ENGINEINSTANCE_H

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

    void stop(void);
    bool run(void);

    virtual bool init(void) = 0;
    virtual void on_stop(void) = 0;
    virtual void render(Graphics* g) = 0;
    virtual void tick(void) = 0;
};

#endif
