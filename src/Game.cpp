#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init()
{
    SDL_WM_SetCaption(TITLE, NULL);
    return true;
}

void Game::on_stop()
{ }

void Game::render(Graphics* g)
{
    g->test();
}

void Game::tick()
{
    if (in->get_key(SDLK_ESCAPE))
        this->stop();    
}
