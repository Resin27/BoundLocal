#include <iostream>
#include "entitymanager.h"
#include "parser.h"
EntityManager::EntityManager()
{
    //Parser parser("testentity.lua");
    //std::cout << "Wait did it actually do it?" << std::endl;
    //luaState = parser.getLuaState();
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
        std::map<std::string, int>::iterator it = prototype.find(entityType);
        if(it == prototype.end())
        {
            Parser parser("testentity.lua");
            LuaRef proto (parser.getLuaState(), parser.getSection(entityType));

            entityCount++; ///This is going to create the new prototyped Entity.
            prototype[entityType] = entityCount-1;

            if((entityMask[entityCount-1] & COMPONENT_PROTOTYPE) == COMPONENT_NONE)
                entityMask[entityCount-1] += COMPONENT_PROTOTYPE;

            if(!proto["position"].isNil())
            {
                if((entityMask[entityCount-1] & COMPONENT_POSITION) == COMPONENT_NONE)
                    entityMask[entityCount-1] += COMPONENT_POSITION;
                positionComponent[entityCount-1] = {0, 0};
            }

            if(!proto["velocity"].isNil())
            {
                if((entityMask[entityCount-1] & COMPONENT_VELOCITY) == COMPONENT_NONE)
                    entityMask[entityCount-1] += COMPONENT_VELOCITY;
                velocityComponent[entityCount-1] = {0, 0};
            }

            if(!proto["hitbox"].isNil())
            {
                if((entityMask[entityCount-1] & COMPONENT_HITBOX) == COMPONENT_NONE)
                    entityMask[entityCount-1] += COMPONENT_HITBOX;
                LuaRef hitbox = proto["hitbox"];
                hitboxComponent[entityCount-1].xHitbox.width = hitbox["xWidth"].cast<float>();
                hitboxComponent[entityCount-1].xHitbox.height = hitbox["xHeight"].cast<float>();
                hitboxComponent[entityCount-1].yHitbox.width = hitbox["yWidth"].cast<float>();
                hitboxComponent[entityCount-1].yHitbox.height = hitbox["yHeight"].cast<float>();
                hitboxComponent[entityCount-1].xOffset = {0, hitbox["xOffset"].cast<int>()};
                hitboxComponent[entityCount-1].yOffset = {hitbox["yOffset"].cast<int>(), 0};
            }

            if(!proto["sprite"].isNil())
            {
                if((entityMask[entityCount-1] & COMPONENT_SPRITE) == COMPONENT_NONE)
                    entityMask[entityCount-1] += COMPONENT_SPRITE;
                ///Okay, let's say fuck this for now and just make the animationManager handle all sprite related shit.
                LuaRef sprite = proto["sprite"];
                spriteComponent[entityCount-1].spritesheet = sprite["spritesheet"].cast<std::string>();
                spriteComponent[entityCount-1].layer = sprite["layer"].cast<int>();
                //spriteComponent[entityCount].sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
                //spriteComponent[entityCount].layer = proto["sprite"]["layer"].cast<int>();
            }

            if(!proto["input"].isNil())
            {
                if((entityMask[entityCount-1] & COMPONENT_INPUT) == COMPONENT_NONE)
                    entityMask[entityCount-1] += COMPONENT_INPUT;
            }

            if(!proto["player"].isNil())
                if((entityMask[entityCount-1] & COMPONENT_PLAYER) == COMPONENT_NONE)
                    entityMask[entityCount-1] += COMPONENT_PLAYER;
        }

        ///Then it'll create that type of entity.
        entityCount++;
        entityMask[entityCount-1] = entityMask[prototype[entityType]] - COMPONENT_PROTOTYPE;

        std::cout << "Prototype's ID is: " << prototype[entityType] << std::endl;

        positionComponent[entityCount-1] = PositionComponent(positionComponent[prototype[entityType]]);
        velocityComponent[entityCount-1] = VelocityComponent(velocityComponent[prototype[entityType]]);
        hitboxComponent[entityCount-1] = HitboxComponent(hitboxComponent[prototype[entityType]]);
        spriteComponent[entityCount-1] = SpriteComponent(spriteComponent[prototype[entityType]]);
        inputComponent[entityCount-1] = InputComponent(inputComponent[prototype[entityType]]);
        playerComponent[entityCount-1] = PlayerComponent(playerComponent[prototype[entityType]]);

        worldChanged = true;
    }
}

void EntityManager::removeEntity(int ID)
{
    ///This block is my first attempt at making sure that the prototypes are always accounted for, even when
    ///Entities are moved around because of removal and whatnot.
    for(std::map<std::string,int>::iterator it = prototype.begin(); it != prototype.end(); it++)
        if(it->second == entityCount-1)
        {
            std::cout << "This happened: " << it->first << ":" << it->second << "->" << ID-1 << std::endl; ///?????????
            prototype[it->first] = ID-1;
            std::cout << "Now prototype[" << it->first << "] = " << it->second << std::endl;
        }
    ///-----------------------------------------------------------------------------------------------------


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
    entityCount--;
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
