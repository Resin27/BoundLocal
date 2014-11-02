#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "system.h"
#include "entitymanager.h"
#include "positioncomponent.h"
#include "spritecomponent.h"

///Class
class RenderSystem : public System
{
protected:

public:

    std::vector<PositionComponent*> backgroundPositionRegister;
    std::vector<PositionComponent*> stagePositionRegister;
    std::vector<PositionComponent*> foregroundPositionRegister;

    std::vector<SpriteComponent*> backgroundSpriteRegister;
    std::vector<SpriteComponent*> stageSpriteRegister;
    std::vector<SpriteComponent*> foregroundSpriteRegister;

    //void draw(sf::RenderWindow& window, PositionComponent *positionComponent, SpriteComponent *spriteComponent);
    void registerEntities(EntityManager& eManager);
    void draw(sf::RenderWindow& window);
};

#endif


