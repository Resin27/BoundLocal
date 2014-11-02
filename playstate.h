#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gamestate.h"
#include <sstream>

class PlayState : public GameState
{
protected:

public:

    //sf::Texture arrows;

    sf::Text debug;


    void init();
    void cleanUp();

    void pause();
    void resume();

    void handleEvents(GameEngine *game);
    void update(GameEngine *game, float dt);
    void draw(GameEngine *game);
};

#endif
