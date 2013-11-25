#include "Instance.hpp"

/* Instance */

Instance::Instance()
{    
    surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
    screen = new Bitmap(WIDTH, HEIGHT);
    in = new InputMan();
}

Instance::~Instance()
{
    delete surface;
    delete in;
    delete screen;
}

/* InstanceMan */

bool InstanceMan::running;

Instance* InstanceMan::inst;

bool InstanceMan::run(Instance* inst_)
{
    inst = inst_;
    if (!inst->init())
        return false;
    running = true;
    Graphics* g;
    SDL_Event evnt;
    while (running) {
        inst->tick();
        g = inst->screen->create_graphics();
        inst->render(g);
        g->destroy();  

        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type) {
            case SDL_QUIT:
                stop();
                break;
            default:
                inst->in->event_proc(evnt);
                break;
            }
        }
        SDL_LockSurface(inst->surface);
        memcpy(inst->surface->pixels, inst->screen->get_pixels(),
              (inst->WIDTH * inst->HEIGHT) << 2);
        SDL_UnlockSurface(inst->surface);
        SDL_Flip(inst->surface);
    }
    _stopped();
    return true;
}

void InstanceMan::_stopped(void)
{
    SDL_Quit();
}

void InstanceMan::stop(void)
{
    inst->on_stop();
    running = false;
}
