#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

class GameState;

///Class
class GameEngine
{
private:

    std::vector<GameState*> states;
    bool running;

    sf::Clock gameClock;
    sf::Time gameTime;
    sf::Time frameLimit;

    int currentFrameCount;
    int lastFrameCount;
    int FPS;
    sf::Time testWhatever;

public:

    sf::RenderWindow window;

    void init();
    void run();
    void cleanUp();

    void changeState(GameState *state);
    void pushState(GameState *state);
    void popState();

    void handleEvents();
    void update(float dt);
    void draw();

    bool isRunning(){return running;}
    void quit(){running = false;}
};

#endif

