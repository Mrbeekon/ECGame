#include "Game.hpp"

Game::Game()
{
    width = 1024;
    height = 768;
    surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    screen = new Bitmap(width, height);
    in = new InputMan();
    rand = new Random();
}

Game::~Game()
{
    delete surface;
    delete screen;
    delete in;
    delete rand;
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
    g->destroy();
}

void Game::_tick()
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
    while (running) {
        _render(screen->create_graphics());
        _tick();
        // Copy pixel data to logical display surface and show
        SDL_LockSurface(surface);
        memcpy(surface->pixels, screen->get_pixels(), (width * height) << 2);
        SDL_UnlockSurface(surface);
        SDL_Flip(surface);
    }
    SDL_Quit();
}