#include <iostream>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"

int main()
{
    GameEngine game;

    game.init();
    game.pushState(new PlayState);

    game.run();

    game.cleanUp();

    return 0;
}
