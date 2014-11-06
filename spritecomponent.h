#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "component.h"

///Class
class SpriteComponent : public Component
{
protected:

public:

    std::string spritesheet;
    sf::Sprite sprite;
    int layer;

    SpriteComponent(){};
    SpriteComponent(SpriteComponent& spriteComponent){spritesheet = spriteComponent.spritesheet; layer = spriteComponent.layer;}

};

#endif
