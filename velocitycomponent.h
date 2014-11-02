#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "component.h"

///Class
class VelocityComponent : public Component
{
protected:

public:

    sf::Vector2f velocity;

    VelocityComponent(){velocity = sf::Vector2f();}
    VelocityComponent(float x, float y){velocity.x = x; velocity.y = y;}//{velocity = sf::Vector2f(x, y);}
    VelocityComponent(VelocityComponent& velocityComponent){velocity = velocityComponent.velocity;}

};

#endif

