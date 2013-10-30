#include "Game.hpp"

Game::Game()
{
    width = DEFWIDTH;
    height = DEFHEIGHT;
    uptime = 0;
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
    g->draw_string(20, 10, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, \n"
                         "sed do eiusmod tempor incididunt ut labore et dolore magna \n"
                         "aliqua. Ut enim ad minim veniam, quis nostrud exercitation \n"
                         "ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis \n"
                         "aute irure dolor in reprehenderit in voluptate velit esse \n"
                         "cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat \n"
                         "cupidatat non proident, sunt in culpa qui officia deserunt \n"
                         "mollit anim id est laborum.", COL_YELLOW);
    g->destroy();
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
