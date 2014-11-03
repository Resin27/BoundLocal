#ifndef WORLD_H
#define WORLD_H

#include "component.h"
#include "positioncomponent.h"
#include "velocitycomponent.h"
#include "hitboxcomponent.h"
#include "spritecomponent.h"
#include "inputcomponent.h"

static const int MAX_ENTITY_COUNT = 128;

/*enum ComponentType
{
    COMPONENT_NONE = 0,
    COMPONENT_POSITION = 1,
    COMPONENT_VELOCITY = 2,
    COMPONENT_HITBOX = 4,
    COMPONENT_SPRITE = 8
};*/


///Struct
class World
{
    public:
        int entityMask[MAX_ENTITY_COUNT];

        PositionComponent positionComponent[MAX_ENTITY_COUNT];
        VelocityComponent velocityComponent[MAX_ENTITY_COUNT];
        HitboxComponent hitboxComponent[MAX_ENTITY_COUNT];
        SpriteComponent spriteComponent[MAX_ENTITY_COUNT];
        InputComponent inputComponent[MAX_ENTITY_COUNT];

        World()
        {
            for(int i = 0; i < MAX_ENTITY_COUNT; i++)
                entityMask[i] = 0;
        }
};

#endif
