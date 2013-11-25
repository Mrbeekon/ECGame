#ifndef ENGINEINSTANCE_H
#define ENGINEINSTANCE_H

#include "ECStd.hpp"
#include "Graphics.hpp"
#include "InputMan.hpp"

class Instance
{
public: 
    const uint WIDTH = 1024, 
               HEIGHT = 768;

    SDL_Surface* surface;

    InputMan* in;
    Bitmap* screen;

    Instance();
    virtual ~Instance();
    virtual bool init(void) = 0;
    virtual void on_stop(void) = 0;
    virtual void render(Graphics* g) = 0;
    virtual void tick(void) = 0;
};

class InstanceMan
{
    static bool running;

    static Instance* inst;

    static void _stopped(void);
public:
    static bool run(Instance* inst_);
    static void stop(void);
};

#endif
