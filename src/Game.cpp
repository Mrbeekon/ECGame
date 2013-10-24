#include "Game.hpp"

Game::Game()
{
    width = DEFWIDTH;
    height = DEFHEIGHT;
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
    g->clear(0)->draw_line(0, 0, width, height, 0xffff00)->draw_line(0, height, width, 0, 0xffff)->destroy();
}

void Game::_tick(TickAtt ta)
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

void Game::_run()
{
    TickAtt ticks;

    while (running) {
        ticks.last = SDL_GetTicks();

        _tick(ticks);
        ticks.tick++;

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
