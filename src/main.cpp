#include "ECStd.hpp"
#include "Instance.hpp"

class Game : public Instance
{
public:
    Game()
    {
    }

    ~Game()
    {
    }

    bool init(void)
    {
        SDL_WM_SetCaption(TITLE, NULL);
        return true;
    }

    void on_stop(void)
    {
    }

    void render(Graphics* g)
    {
        g->test();
    }

    void tick(void)
    {
        if (in->get_key(SDLK_ESCAPE))
            this->stop(); 
    }
};

int main(int argc, char** argv)
{
    Game* game = new Game();
    game->run();
    return EXIT_SUCCESS;
}
