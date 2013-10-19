#include "ec.h"

#include "Graphics.h"
#include "InputMan.h"
#include "Random.h"

const uint FPS = 60,
           WIDTH = DEFWIDTH,
           HEIGHT = DEFHEIGHT;

bool running;

SDL_Surface* surface;
InputMan* in;
Random* rnd;


void Stop()
{
    running = false;
}

void Render(Graphics* g)
{
    g->clear(rnd->next());
}

void Tick()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            in->set_key_down(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            in->set_key_up(event.key.keysym.sym);
            break;
        }
    }

    if (in->get_key(SDLK_ESCAPE))
        running = false;
}

void Run()
{
    Bitmap* screen = new Bitmap(WIDTH, HEIGHT, surface->pixels);
    uint ticks = 0;

    while (running) {
        ticks = SDL_GetTicks();

        Tick();

        Render(screen->create_graphics());
        SDL_Flip(surface);

        if(1000 / FPS > SDL_GetTicks() - ticks) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - ticks));
        }
    }
    SDL_Quit();
}

void Start()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
    in = new InputMan();
    rnd = new Random();
    running = true;
    Run();
}

int main(int argc, char** argv)
{
    Start();
    return EXIT_SUCCESS;
}
