#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "system.h"
#include "entitymanager.h"
#include "positioncomponent.h"
#include "velocitycomponent.h"
#include "hitboxcomponent.h"

///Class
class CollisionSystem : public System
{
protected:

public:

    std::vector<PositionComponent*> positionRegister;
    std::vector<VelocityComponent*> velocityRegister;
    std::vector<HitboxComponent*> hitboxRegister;

    //void registerEntity(int entityID){entityRegister.push_back(entityID);}
    //void unregisterEntity(int entityID);
    void registerEntities(EntityManager& eManager);
    void update();
    //void update(EntityManager& eManager, float dt);

};

#endif


