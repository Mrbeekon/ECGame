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
    int col = RGBINT((byte)abs(sin(uptime / 50.0) * 255),
                     (byte)abs(sin(uptime / 50.0 + PI / 3 * 1) * 255),
                     (byte)abs(sin(uptime / 50.0 + PI / 3 * 2) * 255));
    std::string msg("I &{u}declare&{u} that this text formatting is &{k}good&{k} &{i} excellent.");
    g->draw_string((width - Graphics::measure_string_width(msg)) >> 1,
                   (height - Graphics::measure_string_height(msg)) >> 1,
                   msg, col);
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