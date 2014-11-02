#include "rendersystem.h"

/*void RenderSystem::draw(sf::RenderWindow& window, PositionComponent *positionComponent, SpriteComponent *spriteComponent)
{
    spriteComponent->sprite.setPosition(positionComponent->position);
    window.draw(spriteComponent->sprite);
}*/

void RenderSystem::registerEntities(EntityManager& eManager)
{
    backgroundPositionRegister.clear();
    stagePositionRegister.clear();
    foregroundPositionRegister.clear();

    backgroundSpriteRegister.clear();
    stageSpriteRegister.clear();
    foregroundSpriteRegister.clear();

    for(int entityID = 0; entityID < eManager.entityCount; entityID++)
    {
        if((eManager.entityMask[entityID] & (COMPONENT_POSITION | COMPONENT_SPRITE)) == (COMPONENT_POSITION | COMPONENT_SPRITE))
        {
            switch(eManager.spriteComponent[entityID].layer)
            {
                case -1:
                    backgroundPositionRegister.push_back(&(eManager.positionComponent[entityID]));
                    backgroundSpriteRegister.push_back(&(eManager.spriteComponent[entityID]));
                    break;

                case 0:
                    stagePositionRegister.push_back(&(eManager.positionComponent[entityID]));
                    stageSpriteRegister.push_back(&(eManager.spriteComponent[entityID]));
                    break;

                case 1:
                    foregroundPositionRegister.push_back(&(eManager.positionComponent[entityID]));
                    foregroundSpriteRegister.push_back(&(eManager.spriteComponent[entityID]));
                    break;

                default:
                    std::cout << "Layer of entity " << entityID << " undefined." << std::endl;
            }

        }
    }
}

void RenderSystem::draw(sf::RenderWindow& window)
{
    for(unsigned int i = 0; i < backgroundPositionRegister.size(); i++)
    {
            backgroundSpriteRegister[i]->sprite.setPosition(backgroundPositionRegister[i]->position);
            window.draw(backgroundSpriteRegister[i]->sprite);
    }
    for(unsigned int i = 0; i < stagePositionRegister.size(); i++)
    {
            stageSpriteRegister[i]->sprite.setPosition(stagePositionRegister[i]->position);
            window.draw(stageSpriteRegister[i]->sprite);
    }
    for(unsigned int i = 0; i < foregroundPositionRegister.size(); i++)
    {
            foregroundSpriteRegister[i]->sprite.setPosition(foregroundPositionRegister[i]->position);
            window.draw(foregroundSpriteRegister[i]->sprite);
    }
}

