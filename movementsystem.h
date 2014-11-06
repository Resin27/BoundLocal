#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "system.h"
#include "entitymanager.h"
#include "positioncomponent.h"
#include "velocitycomponent.h"

///Class
class MovementSystem : public System
{
protected:

public:

    std::vector<PositionComponent*> positionRegister;
    std::vector<VelocityComponent*> velocityRegister;

    //void registerEntity(int entityID){entityRegister.push_back(entityID);}
    //void unregisterEntity(int entityID);
    void registerEntities(EntityManager& eManager);
    void update(float dt);

};

#endif

