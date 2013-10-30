#include "Game.hpp"

Game::Game()
{
    width = DEFWIDTH;
    height = DEFHEIGHT;
    uptime = 0;
    surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    screen = new Bitmap(width, height);
    in = new InputMan();
    rnd = new Random();
}

Game::~Game()
{
    delete surface;
    delete screen;
    delete in;
    delete rnd;
}

void Game::start()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption(TITLE, NULL);

    running = true;
    _run();
}

void Game::stop()
{
    running = false;
}

void Game::_render(Graphics* g)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            g->set_pixel(x, y, RGBINT(y * 255 / height, 0, x * 255 / width));
    g->draw_string(0, 0, "Hello, World!", 0xffff00);
}

void Game::_tick(TickAtt ta)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            stop();
            break;
        default:
            in->event_proc(e);
            break;
        }
    }

    if (in->get_key(SDLK_ESCAPE))
        stop();
}

void Game::_run()
{
    TickAtt ticks;

    while (running) {
        ticks.last = SDL_GetTicks();

        _tick(ticks);
        ticks.tick++;
        uptime++;

        _render(screen->create_graphics());

        SDL_LockSurface(surface);
        memcpy(surface->pixels, screen->get_pixels(), (width * height) << 2);
        SDL_UnlockSurface(surface);
        SDL_Flip(surface);

        if(1000 / FPS > SDL_GetTicks() - ticks.last) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - ticks.last));
        }
    }
    SDL_Quit();
}

int main(int argc, char** argv)
{
    Game* g = new Game();
    g->start();
    return EXIT_SUCCESS;
}
