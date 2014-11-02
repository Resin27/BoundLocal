#include "movementsystem.h"

/*void MovementSystem::unregisterEntity(int entityID)
{
    for(unsigned int i = 0; i < entityRegister.size(); i++)
        if(entityRegister[i] == entityID)
            entityRegister.erase(entityRegister.begin() + i);
}

void MovementSystem::update(EntityManager& eManager, float dt)
{
    for(unsigned int i = 0; i < entityRegister.size(); i++)
    {
        eManager.positionComponent[entityRegister[i]].position += eManager.velocityComponent[entityRegister[i]].velocity * dt;
    }
    /*positionComponent->position += velocityComponent->velocity * dt;
    velocityComponent->velocity.x = 0;
    velocityComponent->velocity.y = 0;
}*/

void MovementSystem::registerEntities(EntityManager& eManager)
{
    positionRegister.clear();
    velocityRegister.clear();
    for(int entityID = 0; entityID < eManager.entityCount; entityID++)
    {
        if((eManager.entityMask[entityID] & (COMPONENT_POSITION | COMPONENT_VELOCITY)) == (COMPONENT_POSITION | COMPONENT_VELOCITY))
        {
            positionRegister.push_back(&(eManager.positionComponent[entityID]));
            velocityRegister.push_back(&(eManager.velocityComponent[entityID]));
        }
    }
}

void MovementSystem::update(float dt)
{
    for(unsigned int i = 0; i < positionRegister.size(); i++)
    {
        /*if(std::abs(positionRegister[i]->position.x - positionRegister[i]->oldPosition.x) < 0.0000003125) ///0.03125 m/s = 1 pixel/s
            velocityRegister[i]->velocity.x = 0;
        if(std::abs(positionRegister[i]->position.y - positionRegister[i]->oldPosition.y) < 0.0000003125)
            velocityRegister[i]->velocity.y = 0;*/

        positionRegister[i]->oldPosition = positionRegister[i]->position;
        positionRegister[i]->position += velocityRegister[i]->velocity * dt;
    }
}
