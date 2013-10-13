#include "stdafx.h"

int main(int argc, char** argv)
{
    const int FPS = 60, 
              WIDTH = 800, 
              HEIGHT = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;
    unsigned int tick = 0;

    Screen* screen = new Screen(WIDTH, HEIGHT);
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
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
            }
        }

        screen->Clear(0);
        screen->DrawRectangle(WIDTH / 8, HEIGHT / 8, WIDTH / 8 * 6, HEIGHT / 8 * 6, 0x8888, 0xffff, 4);

        SDL_Flip(screen->GetSurface());
        if(1000 / FPS > SDL_GetTicks() - tick) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
