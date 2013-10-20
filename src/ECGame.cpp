#include "ec.h"

#include "Graphics.h"
#include "InputMan.h"
#include "Random.h"

class Game
{
public:
    bool running;
    SDL_Surface*    surface;
    Bitmap*         screen;
    InputMan*       in;
    Random*         rnd;

    Game()
    {
        int width = DEFWIDTH,
            height = DEFHEIGHT;
        surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
        screen = new Bitmap(width, height, surface->pixels);
        in = new InputMan();
        rnd = new Random();
    }

    ~Game()
    {
        delete surface;
        delete screen;
        delete in;
        delete rnd;
    }

    void Start()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_WM_SetCaption(TITLE, NULL);

        running = true;
        Run();
    }

    void Stop()
    {
        running = false;
    }

    void Render(int tick, Graphics* g)
    {
        g->clear(0x88);
    }

    void Tick(int tick)
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
        uint ticks = 0;

        while (running) {
            ticks = SDL_GetTicks();

            Tick(ticks);

            Render(ticks, screen->create_graphics());
            SDL_Flip(surface);

            if(1000 / FPS > SDL_GetTicks() - ticks) {
                SDL_Delay(1000 / FPS - (SDL_GetTicks() - ticks));
            }
        }
        SDL_Quit();
    }
};

int main(int argc, char** argv)
{
    Game* g = new Game();
    g->Run();
    return EXIT_SUCCESS;
}
