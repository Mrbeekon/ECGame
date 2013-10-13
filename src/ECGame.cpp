#include <SDL/SDL.h>
#include <iostream>
using namespace std;

class Screen
{
public:
    Screen(int w, int h) 
    {
        width = w;
        height = h;
        surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
        Clear(0);
    }

    ~Screen()
    {
        delete surface;
    }

    SDL_Surface* GetSurface()
    {
        return surface;
    }

    void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
    {
        unsigned int* pixel = (unsigned int*)(surface->pixels) + x + y * width;
        *pixel = SDL_MapRGB(surface->format, r, g, b);
    }

    void SetPixel(int x, int y, int c)
    {
        SetPixel(x, y, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff);
    }

    void Clear(int c)
    {
        for (int i = 0; i < width * height; i++)
            SetPixel(i, 0, c);
    }
private:	
    SDL_Surface* surface;
    int width, height;
};

int main(int argc, char** argv)
{
    const int FPS = 60, 
              WIDTH = 800, 
              HEIGHT = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;
    unsigned int start = 0;

    Screen* screen = new Screen(WIDTH, HEIGHT);

    while(running) {
        start = SDL_GetTicks();

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

        //screen->Clear(0);
        for (int i = 0; i < WIDTH * HEIGHT; i++)
            screen->SetPixel(i, 0, i + SDL_GetTicks() << 8 | i + SDL_GetTicks());

        SDL_Flip(screen->GetSurface());
        if(1000 / FPS > SDL_GetTicks() - start) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }
    }

    SDL_Quit();
    return 0;
}
