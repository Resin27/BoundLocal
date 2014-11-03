#include "gameengine.h"
#include "gamestate.h"
#include <iostream>

#include "parser.h"

void GameEngine::init()
{
    Parser parser("config.lua");

    int screenWidth, screenHeight;
    bool isFullscreen;
    std::string title;

    title = parser.getString("window", "title");
    screenWidth = parser.getInt("window", "width");
    screenHeight = parser.getInt("window", "height");
    isFullscreen = parser.getBool("window", "fullscreen");

    window.create(sf::VideoMode(screenWidth, screenHeight), title, (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default));

    gameClock.restart();
    gameTime = gameClock.getElapsedTime();
    running = true;

    ///TESTING SHIT
    currentFrameCount = 0;
    lastFrameCount = 0;
    FPS = 0;
    testWhatever = sf::milliseconds(0);
}

void GameEngine::cleanUp()
{
    while(!states.empty())
    {
        states.back()->cleanUp();
        states.pop_back();
    }
    window.close();
}

void GameEngine::changeState(GameState *state)
{
    if(!states.empty())
    {
        states.back()->cleanUp();
        states.pop_back();
    }

    states.push_back(state);
    states.back()->init();
}

void GameEngine::pushState(GameState *state)
{
    if(!states.empty())
        states.back()->pause();

    states.push_back(state);
    states.back()->init();
}

void GameEngine::popState()
{
    if(!states.empty())
    {
        states.back()->cleanUp();
        states.pop_back();
    }

    if(!states.empty())
        states.back()->resume();
}

void GameEngine::handleEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
        if(event.type == sf::Event::Closed)
            quit();
    if(!states.empty())
        states.back()->handleEvents(this);
}

void GameEngine::update(float dt)
{
    /*sf::Time newTime = gameClock.getElapsedTime();
    sf::Time frameTime = newTime - gameTime;
    gameTime = newTime;*/

    //std::cout << gameTime.asSeconds() << std::endl;

    if(!states.empty())
        states.back()->update(this, dt);
}

void GameEngine::draw()
{
    if(!states.empty())
        states.back()->draw(this);
}


///--------------------------------------------------------------------------------------------------------------------
///This nonsense here has to be tidied up. I think there are some redundancies around here somewhere.
///Things can't be named "testWhatever" and less magic numbers.
void GameEngine::run()
{
    while(isRunning())
    {
        sf::Time newTime = gameClock.getElapsedTime();
        sf::Time frameTime = newTime - gameTime;
        gameTime = newTime;

        frameLimit += frameTime;
        testWhatever += frameTime;

        handleEvents();
        update(frameTime.asSeconds());
        if(frameLimit.asSeconds() >= 1.f/120.f)
        {
            currentFrameCount++;
            draw();
            //std::cout << 1.f/frameTime.asSeconds() << std::endl;
            frameLimit = sf::milliseconds(0);
        }
        if(testWhatever.asSeconds() >= 1.f)
        {
            currentFrameCount -= lastFrameCount;
            lastFrameCount = currentFrameCount;
            std::cout << currentFrameCount/(int)testWhatever.asSeconds();
            testWhatever = sf::milliseconds(0);
        }
    }
}
