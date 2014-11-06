#include "movementsystem.h"

void MovementSystem::registerEntities(EntityManager& eManager)
{
    positionRegister.clear();
    velocityRegister.clear();
    for(int entityID = 0; entityID < eManager.entityCount; entityID++)
    {
        if((eManager.entityMask[entityID] & (COMPONENT_POSITION | COMPONENT_VELOCITY)) == (COMPONENT_POSITION | COMPONENT_VELOCITY) && !(eManager.entityMask[entityID] & COMPONENT_PROTOTYPE))
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
        positionRegister[i]->oldPosition = positionRegister[i]->position;
        positionRegister[i]->position += velocityRegister[i]->velocity * dt;
    }
}
