#ifndef GAME_H
#define GAME_H

#include "ECStd.hpp"
#include "Instance.hpp"

class Game : public Instance
{
public:
    const char* TITLE = "ECGame";
    Game();
    ~Game();
    bool init(void);
    void on_stop(void);
    void render(Graphics* g);
    void tick(void);
};

#endif
