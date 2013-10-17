#include "SDL/SDL.h"
#include "c_types.h"
#include "Screen.h"
#include "InputMan.h"
#include "Random.h"

int main(int argc, char** argv)
{
    const uint FPS = 60, 
               WIDTH = 800, 
               HEIGHT = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;
    uint tick = 0;
    
    Screen* screen = new Screen(WIDTH, HEIGHT);
    InputMan* in = new InputMan();
    Random* rand = new Random();

    while(running) {
        tick = SDL_GetTicks();

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
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
        if (in->get_key(SDLK_SPACE))
            screen->fill_circle(rand->next(WIDTH - 100), rand->next(HEIGHT - 100), rand->next(50), rand->next());

        SDL_Flip(screen->get_surface());
        if(1000 / FPS > SDL_GetTicks() - tick) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
