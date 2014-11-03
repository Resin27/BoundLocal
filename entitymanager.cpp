#include <iostream>
#include "entitymanager.h"
#include "parser.h"
EntityManager::EntityManager()
{
    entityCount = 0;
    {
        for(int i = 0; i < MAX_ENTITY_COUNT; i++)
            entityMask[i] = COMPONENT_NONE;
    }
    worldChanged = false;
}

void EntityManager::addEntity()
{
    if(entityCount < MAX_ENTITY_COUNT)
    {
        ++entityCount;
        worldChanged = true;
    }
}

void EntityManager::addEntity(const std::string& entityType)
{
    if(entityCount < MAX_ENTITY_COUNT)
    {
        Parser parser("testentity.lua");
        std::map<std::string, LuaRef>::iterator it = prototype.find(entityType);
        if(it == prototype.end())
        {
            ///prototype[entityType](parser.getSection(entityType));
            prototype.insert(std::pair<std::string, LuaRef>(entityType, parser.getSection(entityType)));
            ///Load the EntityType from file.
        }
        ///Then it'll create that type of entity.
        entityCount++;
        worldChanged = true;
    }
}

void EntityManager::removeEntity(int ID)
{
    entityMask[ID] = entityMask[entityCount - 1];
    entityMask[entityCount - 1] = COMPONENT_NONE;
    positionComponent[ID] = PositionComponent(positionComponent[entityCount - 1]);
    //delete world.positionComponent[entityCount];
    velocityComponent[ID] = VelocityComponent(velocityComponent[entityCount - 1]);
    //delete world.velocityComponent[entityCount];
    hitboxComponent[ID] = HitboxComponent(hitboxComponent[entityCount - 1]);
    //delete world.hitboxComponent[entityCount];
    spriteComponent[ID] = SpriteComponent(spriteComponent[entityCount - 1]);
    inputComponent[ID] = InputComponent(inputComponent[entityCount - 1]);
    playerComponent[ID] = PlayerComponent(playerComponent[entityCount - 1]);
    //delete world.spriteComponent[entityCount];
    --entityCount;
    worldChanged = true;
}

void EntityManager::removeAllEntities()
{
        for(int i = 0; i < MAX_ENTITY_COUNT; i++)
        {
            entityMask[i] = COMPONENT_NONE;
            //delete world.positionComponent[entityCount];
            //delete world.velocityComponent[entityCount];
            //delete world.hitboxComponent[entityCount];
            //delete world.spriteComponent[entityCount];
        }
        entityCount = 0;
        worldChanged = true;
}

void EntityManager::addComponent(int ID, ComponentType componentType)
{
    if((entityMask[ID] & componentType) == COMPONENT_NONE)
    {
        entityMask[ID] += componentType;
        /*switch(componentType)
        {
            case COMPONENT_NONE:
                break;
            case COMPONENT_POSITION:
                //world.positionComponent[ID] = new PositionComponent();
                //MovementSystem
                break;
            case COMPONENT_VELOCITY:
                //world.velocityComponent[ID] = new VelocityComponent();
                break;
            case COMPONENT_HITBOX:
                //world.hitboxComponent[ID] = new HitboxComponent();
                break;
            case COMPONENT_SPRITE:
                //world.spriteComponent[ID] = new SpriteComponent();
                break;
            case COMPONENT_INPUT:
                //world.inputComponent[ID] = new InputComponent();
                break;
        }*/
        worldChanged = true;
    }
}

void EntityManager::removeComponent(int ID, ComponentType componentType)
{
    if((entityMask[ID] & componentType) != COMPONENT_NONE)
    {
        entityMask[ID] -= componentType;
        worldChanged = true;
    }
}

void EntityManager::printEntities()
{
    for(int i = 0; i < entityCount; i++)
    {
        if((entityMask[i] & (COMPONENT_POSITION | COMPONENT_VELOCITY)) != COMPONENT_NONE)
        std::cout << i << " " << positionComponent[i].position.x << "," << positionComponent[i].position.y << " " <<velocityComponent[i].velocity.x << "," << velocityComponent[i].velocity.y << std::endl;
    }
    std::cout << std::endl;
}

/*void EntityManager::createEntity(World& world, std::string entityType)
{
    addEntity();
    Parser parser;
    parser.openFile("testentity.txt");
    parser.closeFile();
    if(!(parser.options["entityType"]["xpos"] == ""))
    {
        addComponent(world, entityCount, COMPONENT_POSITION);
        world.positionComponent[entityCount]->position.x = atoi(parser.options["entityType"]["xpos"].c_str());
        world.positionComponent[entityCount]->position.y = atoi(parser.options["entityType"]["ypos"].c_str());
    }
    if(!(parser.options["entityType"]["spritesheet"] == ""))
    {

    }
}*/
