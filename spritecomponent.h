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

    sf::Sprite sprite;
    int layer;

};

#endif
