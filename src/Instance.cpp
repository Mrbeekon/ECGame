#include "Instance.hpp"

/* Instance */

Instance::Instance()
{    
    _running = false;

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

void Instance::stop(void)
{
    this->on_stop();
    _running = false;
}

bool Instance::run(void)
{
    if (!this->init())
        return false;

    SDL_Init(SDL_INIT_EVERYTHING);
    _running = true;

    Graphics* g;
    SDL_Event evnt;

    while (_running) {
        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type) {
            case SDL_QUIT:
                stop();
                break;
            default:
                this->in->event_proc(evnt);
                break;
            }
        }
        this->tick();

        g = this->screen->create_graphics();
        this->render(g);
        g->destroy();  
        SDL_LockSurface(this->surface);
        memcpy(this->surface->pixels, this->screen->get_pixels(),
              (this->WIDTH * this->HEIGHT) << 2);
        SDL_UnlockSurface(this->surface);
        SDL_Flip(this->surface);
    }

    SDL_Quit();

    return true;
}
