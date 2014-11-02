#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "parser.h"
#include "component.h"
#include "positioncomponent.h"
#include "velocitycomponent.h"
#include "hitboxcomponent.h"
#include "spritecomponent.h"
#include "inputcomponent.h"
#include "playercomponent.h"
///#include "world.h"

static const int MAX_ENTITY_COUNT = 128;

enum ComponentType
{
    COMPONENT_NONE = 0,
    COMPONENT_POSITION = 1,
    COMPONENT_VELOCITY = 2,
    COMPONENT_HITBOX = 4,
    COMPONENT_SPRITE = 8,
    COMPONENT_INPUT = 16,
    COMPONENT_PLAYER = 32
};

///Class
class EntityManager
{
protected:

public:

    int entityCount;
    int entityMask[MAX_ENTITY_COUNT];
    bool worldChanged;

    std::map<std::string, LuaRef> prototype;

    PositionComponent positionComponent[MAX_ENTITY_COUNT];
    VelocityComponent velocityComponent[MAX_ENTITY_COUNT];
    HitboxComponent hitboxComponent[MAX_ENTITY_COUNT];
    SpriteComponent spriteComponent[MAX_ENTITY_COUNT];
    InputComponent inputComponent[MAX_ENTITY_COUNT];
    PlayerComponent playerComponent[MAX_ENTITY_COUNT];


    EntityManager();

    void addEntity();
    void addEntity(int entityType); ///Here, int will be the "entityType." Which will be determined from the streamed world info.
    void removeEntity(int ID);
    void removeAllEntities();
    void addComponent(int ID, ComponentType componentType);
    void removeComponent(int ID, ComponentType componentType);

    void printEntities();
    //void createEntity(World& world, std::string entityType);

};

#endif
