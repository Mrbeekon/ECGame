#include "ec.h"

#include "Graphics.h"
#include "InputMan.h"
#include "Random.h"

void Render(Graphics* g)
{
    g->clear(0x88);
}

int main(int argc, char** argv)
{
    const uint FPS = 60, 
               WIDTH = 800, 
               HEIGHT = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;
    uint tick = 0;

    SDL_Surface* surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
        
    Bitmap* screen = new Bitmap(WIDTH, HEIGHT, surface->pixels);

    InputMan* in = new InputMan();
    Random* rand = new Random();

    while (running) {
        tick = SDL_GetTicks();

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

        Render(screen->create_graphics());

        SDL_Flip(surface);
        if(1000 / FPS > SDL_GetTicks() - tick) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
