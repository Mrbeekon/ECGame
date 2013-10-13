#include <SDL/SDL.h>
#include <iostream>
#include <cmath>
#include "Random.h"
using namespace std;

class Screen
{
public:
    int width, height;

    Screen(int w, int h) 
    {
        width = w;
        height = h;
        surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
        Clear(0);
    }

    ~Screen(void)
    {
        delete surface;
    }

    SDL_Surface* GetSurface(void)
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
        if (x < 0 | y < 0 | x >= width | y >= height)
            return;
        SetPixel(x, y, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff);
    }

    void Clear(int c)
    {
        for (int i = 0; i < width * height; i++) {
            unsigned int* pixel = (unsigned int*)(surface->pixels) + i;
            *pixel = SDL_MapRGB(surface->format, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff);
        }
    }
    
    void DrawRectangle(int x, int y, int w, int h, int fc, int bc, int bt) /* 'fc' is fill colour, 
                                                                            * 'bc' border colour, and
                                                                            * 'bt' border thickness. */
    {
        for (int yy = 0; yy < h; yy++)
            for (int xx = 0; xx < w; xx++)
            {
                int c = fc;
                if (yy < bt | yy >= h - bt | xx < bt | xx >= w - bt)
                    c = bc;
                SetPixel(x + xx, y + yy, c);
            }
    }

    void DrawCircle(int x, int y, int r, int c)
    {
        for (int yy = -r; yy < r; yy++)
            for (int xx = -r; xx < r; xx++)
                if (yy * yy + xx * xx < r * r)
                    SetPixel(x + xx, y + yy, c);
    }

    void DrawLine(int x0, int y0, int x1, int y1, int c)
    {
        int dx = abs(x1 - x0),
            dy = abs(y1 - y0),
            sx = x0 < x1 ? 1 : -1,
            sy = y0 < y1 ? 1 : -1,
            err = dx - dy;
        for (; ; )
        {
            SetPixel(x0, y0, c);
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = err << 1;
            if (e2 > -dy)
            {
                err -= dy;
                x0 += sx;
            }
            if (x0 == x1 && y0 == y1)
            {
                SetPixel(x0, y0, c);
                break;
            }
            if (e2 < dx)
            {
                err += dx;
                y0 += sy;
            }
        }
    }
private:	
    SDL_Surface* surface;
};

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
