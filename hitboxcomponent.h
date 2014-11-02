#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "component.h"

///Class
class HitboxComponent : public Component
{
protected:

public:

    sf::Vector2i xOffset;
    sf::Vector2i yOffset;
    sf::FloatRect xHitbox;
    sf::FloatRect yHitbox;

    HitboxComponent(){xOffset = sf::Vector2i(); yOffset = sf::Vector2i(); xHitbox = sf::FloatRect(); yHitbox = sf::FloatRect();}
    HitboxComponent(HitboxComponent& hitboxComponent){xOffset = sf::Vector2i(); yOffset = sf::Vector2i(); xHitbox = hitboxComponent.xHitbox; yHitbox = hitboxComponent.yHitbox;}

};

#endif

