#include <SDL/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen;
    bool running = true;
    const int FPS = 30;
    Uint32 start;
    while(running) {
        start = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
	   }

        // logic

        screen = SDL_SetVideoMode(480, 480, 32, SDL_SWSURFACE);

        Uint32 * pixels = (Uint32*)screen->pixels;
        for(int i = 0; i < 480; i += 1) {
            Uint32* pixel = pixels + i*screen->pitch/4 + SDL_GetTicks()%480;
            *pixel = SDL_MapRGB(screen->format,0xff,0xff,0xff);
        }
        for(int i = 0; i < 480; i += 1) {
            Uint32* pixel = pixels + SDL_GetTicks()%480*screen->pitch/4 + i;
            *pixel = SDL_MapRGB(screen->format,0xff,0xff,0xff);
        }

        //cout << SDL_GetTicks() << endl;

        //render
        SDL_Flip(screen);
        if(1000/FPS > SDL_GetTicks()-start) {
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
    }
    SDL_Quit();
    return 0;
}
