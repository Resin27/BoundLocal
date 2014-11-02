#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "component.h"

///Class
class PositionComponent : public Component
{
protected:

public:

    sf::Vector2f oldPosition;
    sf::Vector2f position;

    PositionComponent(){oldPosition = sf::Vector2f(); position = sf::Vector2f();}
    PositionComponent(float x, float y){oldPosition = position; position.x = x; position.y = y;}
    PositionComponent(PositionComponent& positionComponent){oldPosition = position; position = positionComponent.position;}

};

#endif

