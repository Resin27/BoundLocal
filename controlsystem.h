#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "system.h"
#include "entitymanager.h"
#include "inputcomponent.h"
#include "playercomponent.h"
//#include "aicomponent.h"

///Class
class ControlSystem : public System
{
protected:

public:

    /*std::map<StateType, State> testStateMachine;

    void lookLeft();
    void lookRight();

    ControlSystem();*/

    std::vector<PlayerComponent*> playerRegister;
    std::vector<InputComponent*> playerInputRegister;
    ///For AIComponents
    /*std::vector<AIComponent*> aiRegister;
    std::vector<InputComponent*> aiInputRegister;*/

    //void draw(sf::RenderWindow& window, PositionComponent *positionComponent, SpriteComponent *spriteComponent);
    void registerEntities(EntityManager& eManager);
    void update();
    //void draw(sf::RenderWindow& window);

    //void doNothing();


};

#endif
