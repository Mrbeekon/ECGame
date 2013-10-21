#include "Game.hpp"

Game::Game()
{
    int width = DEFWIDTH,
        height = DEFHEIGHT;
    surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    screen = new Bitmap(width, height, surface->pixels);
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

void Game::Start()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption(TITLE, NULL);

    running = true;
    Run();
}

void Game::Stop()
{
    running = false;
}

void Game::Render(Graphics* g)
{
    g->clear(0)->draw_line(0, 0, DEFWIDTH, DEFHEIGHT, 0xffff00)->draw_line(0, DEFHEIGHT, DEFWIDTH, 0, 0xffff)->destroy();
}

void Game::Tick(TickAtt ta)
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

void Game::Run()
{
    TickAtt ticks;

    while (running) {
        ticks.last = SDL_GetTicks();

        Tick(ticks);
        ticks.tick++;

        Render(screen->create_graphics());
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
    g->Start();
    return EXIT_SUCCESS;
}
