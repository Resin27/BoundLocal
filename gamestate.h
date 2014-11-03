#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "gameengine.h"
#include "inputmanager.h"
#include "entitymanager.h"
#include "assetmanager.h"
#include "debugmanager.h"
#include "movementsystem.h"
#include "collisionsystem.h"
#include "rendersystem.h"

///Class
class GameState
{
protected:

public:

    InputManager inManager;
    EntityManager eManager;
    AssetManager assetManager;
    DebugManager debugManager;
    MovementSystem moveSys;
    CollisionSystem collSys;
    RenderSystem drawSys;

    virtual void init() = 0;
    virtual void cleanUp() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents(GameEngine *game) = 0;
    virtual void update(GameEngine *game, float dt) = 0;
    virtual void draw(GameEngine *game) = 0;

    void changeState(GameEngine *game, GameState* state){game->changeState(state);}
};

#endif

