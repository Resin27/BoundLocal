#include "collisionsystem.h"

void CollisionSystem::registerEntities(EntityManager& eManager)
{
    positionRegister.clear();
    velocityRegister.clear();
    hitboxRegister.clear();

    for(int entityID = 0; entityID < eManager.entityCount; entityID++)
    {
        if((eManager.entityMask[entityID] & (COMPONENT_POSITION | COMPONENT_VELOCITY | COMPONENT_HITBOX)) == (COMPONENT_POSITION | COMPONENT_VELOCITY | COMPONENT_HITBOX))
        {
            positionRegister.push_back(&(eManager.positionComponent[entityID]));
            velocityRegister.push_back(&(eManager.velocityComponent[entityID]));
            hitboxRegister.push_back(&(eManager.hitboxComponent[entityID]));
        }
    }

    for(int entityID = 0; entityID < eManager.entityCount; entityID++)
    {
        if(!((eManager.entityMask[entityID] & (COMPONENT_POSITION | COMPONENT_VELOCITY | COMPONENT_HITBOX)) == (COMPONENT_POSITION | COMPONENT_VELOCITY | COMPONENT_HITBOX))
           && (eManager.entityMask[entityID] & (COMPONENT_POSITION | COMPONENT_HITBOX)) == (COMPONENT_POSITION | COMPONENT_HITBOX))
        {
            positionRegister.push_back(&(eManager.positionComponent[entityID]));
            hitboxRegister.push_back(&(eManager.hitboxComponent[entityID]));
        }
    }
}

void CollisionSystem::update()
{
    for(unsigned int i = 0; i < velocityRegister.size(); i++)
    {
        float dx = positionRegister[i]->position.x - positionRegister[i]->oldPosition.x;
        float dy = positionRegister[i]->position.y - positionRegister[i]->oldPosition.y;

        hitboxRegister[i]->xHitbox.left = positionRegister[i]->position.x + hitboxRegister[i]->xOffset.x;
        hitboxRegister[i]->xHitbox.top = positionRegister[i]->position.y + hitboxRegister[i]->xOffset.y;

        hitboxRegister[i]->yHitbox.left = positionRegister[i]->position.x + hitboxRegister[i]->yOffset.x;
        hitboxRegister[i]->yHitbox.top = positionRegister[i]->position.y + hitboxRegister[i]->yOffset.y;

        for(unsigned int j = 0; j < positionRegister.size(); j++)
        {
            ///This check was used to make sure that an object doesn't collide with itself. Coupled with j = 0 in the for-loop
            ///As is, objects only check collisions with objects behind them in the list
            ///Need to set up some sort of message system to deal with different types of collisions.
            if(i != j)
            {
                hitboxRegister[j]->xHitbox.left = positionRegister[j]->position.x + hitboxRegister[j]->xOffset.x;
                hitboxRegister[j]->xHitbox.top = positionRegister[j]->position.y + hitboxRegister[j]->xOffset.y;

                if(dx > 0)
                    if(hitboxRegister[j]->xHitbox.contains(hitboxRegister[i]->xHitbox.left + hitboxRegister[i]->xHitbox.width, hitboxRegister[i]->xHitbox.top) ||
                       hitboxRegister[j]->xHitbox.contains(hitboxRegister[i]->xHitbox.left + hitboxRegister[i]->xHitbox.width, hitboxRegister[i]->xHitbox.top + hitboxRegister[i]->xHitbox.height))
                    {
                        positionRegister[i]->position.x -= (hitboxRegister[i]->xHitbox.left + hitboxRegister[i]->xHitbox.width) - hitboxRegister[j]->xHitbox.left;
                        velocityRegister[i]->velocity.x = 0.f;
                    }
                if(dx < 0)
                    if(hitboxRegister[j]->xHitbox.contains(hitboxRegister[i]->xHitbox.left, hitboxRegister[i]->xHitbox.top) ||
                       hitboxRegister[j]->xHitbox.contains(hitboxRegister[i]->xHitbox.left, hitboxRegister[i]->xHitbox.top + hitboxRegister[i]->xHitbox.height))
                    {
                        positionRegister[i]->position.x -= hitboxRegister[i]->xHitbox.left - (hitboxRegister[j]->xHitbox.left + hitboxRegister[j]->xHitbox.width);
                        velocityRegister[i]->velocity.x = 0.f;
                    }
                /*if(hitboxRegister[i]->xHitbox.intersects(hitboxRegister[j]->xHitbox))
                {
                    if(dx > 0)
                        positionRegister[i]->position.x -= (hitboxRegister[i]->xHitbox.left + hitboxRegister[i]->xHitbox.width) - hitboxRegister[j]->xHitbox.left;
                    else if (dx < 0)
                        positionRegister[i]->position.x += hitboxRegister[i]->xHitbox.left - (hitboxRegister[j]->xHitbox.left + hitboxRegister[j]->xHitbox.width);

                }*/

                hitboxRegister[j]->yHitbox.left = positionRegister[j]->position.x + hitboxRegister[j]->yOffset.x;
                hitboxRegister[j]->yHitbox.top = positionRegister[j]->position.y + hitboxRegister[j]->yOffset.y;

                if(dy > 0)
                    if(hitboxRegister[j]->yHitbox.contains(hitboxRegister[i]->yHitbox.left, hitboxRegister[i]->yHitbox.top + hitboxRegister[i]->yHitbox.height) ||
                       hitboxRegister[j]->yHitbox.contains(hitboxRegister[i]->yHitbox.left + hitboxRegister[i]->yHitbox.width, hitboxRegister[i]->yHitbox.top + hitboxRegister[i]->yHitbox.height))
                       {
                            positionRegister[i]->position.y -= (hitboxRegister[i]->yHitbox.top + hitboxRegister[i]->yHitbox.height) - hitboxRegister[j]->yHitbox.top;
                            velocityRegister[i]->velocity.y = 0.f;
                       }
                if(dy < 0)
                    if(hitboxRegister[j]->yHitbox.contains(hitboxRegister[i]->yHitbox.left, hitboxRegister[i]->yHitbox.top) ||
                       hitboxRegister[j]->yHitbox.contains(hitboxRegister[i]->yHitbox.left + hitboxRegister[i]->yHitbox.width, hitboxRegister[i]->yHitbox.top))
                       {
                            positionRegister[i]->position.y -= hitboxRegister[i]->yHitbox.top - (hitboxRegister[j]->yHitbox.top + hitboxRegister[j]->yHitbox.height);
                            velocityRegister[i]->velocity.y = 0.f;
                       }
            }
        }

            /*if(hitboxRegister[i]->yHitbox.intersects(hitboxRegister[j]->yHitbox))
            {
                if(dy > 0)
                    positionRegister[i]->position.y -= (hitboxRegister[i]->yHitbox.top + hitboxRegister[i]->yHitbox.height) - hitboxRegister[j]->yHitbox.top;
                else if (dy < 0)
                    positionRegister[i]->position.y += hitboxRegister[i]->yHitbox.top - (hitboxRegister[j]->yHitbox.top + hitboxRegister[j]->yHitbox.height);

            }*/
        //}
    }
}

