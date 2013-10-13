#include <SDL/SDL.h>
#include <iostream>
#include <cmath>
#include "Random.h"
#include "Screen.h"
using namespace std;

int main(int argc, char** argv)
{
    const int FPS = 30, 
              WIDTH = 800, 
              HEIGHT = 600;
    const double PI = 3.1415926535897;

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

        for (int y = 0; y < HEIGHT; y++)
            for (int x = 0; x < WIDTH; x++)
                screen->SetPixel(x, y, x * 255 / WIDTH | y * 255 / HEIGHT << 8);

        double x1 = WIDTH / 2 + sin(tick / 360.0) * HEIGHT / 8 * 3;
        double y1 = HEIGHT / 2 + cos(tick / 360.0) * HEIGHT / 8 * 3;
        double x2 = WIDTH / 2 + sin(tick / 360.0 + PI * 2 / 3) * HEIGHT / 8 * 3;
        double y2 = HEIGHT / 2 + cos(tick / 360.0 + PI * 2 / 3) * HEIGHT / 8 * 3;
        double x3 = WIDTH / 2 + sin(tick / 360.0 + PI * 4 / 3) * HEIGHT / 8 * 3;
        double y3 = HEIGHT / 2 + cos(tick / 360.0 + PI * 4 / 3) * HEIGHT / 8 * 3;
        screen->DrawLine(x1, y1, x2, y2, 0xffff00);
        screen->DrawLine(x2, y2, x3, y3, 0xffff00);
        screen->DrawLine(x3, y3, x1, y1, 0xffff00);

        SDL_Flip(screen->GetSurface());
        if(1000 / FPS > SDL_GetTicks() - tick) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
        }
    }

    SDL_Quit();
    return 0;
}
