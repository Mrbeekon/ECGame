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
    InMan* inm = new InMan();
    Random* rand = new Random();
        
    int col = rand->Next();

    while(running) {
        tick = SDL_GetTicks();

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                inm->SetKeyDown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                inm->SetKeyUp(event.key.keysym.sym);
                break;
            }
        }

        if (inm->GetKey(SDLK_ESCAPE))
            running = false;
        if (inm->GetKey(SDLK_SPACE))
            col = rand->Next();

        screen->Clear(0);
        const int SIZE = HEIGHT / 8;
        for (int i = 0; i < HEIGHT; i += SIZE)
            screen->DrawRectangle(WIDTH / 2 + (int)(sin(tick / 360.0 + HEIGHT / 360.0 * i) * (WIDTH / 2.0) - SIZE / 2), i, 
                                  SIZE, SIZE, col, 0, 0);

        SDL_Flip(screen->GetSurface());
        if(1000 / FPS > SDL_GetTicks() - tick) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
