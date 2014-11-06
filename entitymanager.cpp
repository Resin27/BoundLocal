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
            prototype[entityType] = entityCount;

            if((entityMask[entityCount] & COMPONENT_PROTOTYPE) == COMPONENT_NONE)
                entityMask[entityCount] += COMPONENT_PROTOTYPE;

            if(!proto["position"].isNil())
            {
                if((entityMask[entityCount] & COMPONENT_POSITION) == COMPONENT_NONE)
                    entityMask[entityCount] += COMPONENT_POSITION;
                positionComponent[entityCount] = {0, 0};
            }

            if(!proto["velocity"].isNil())
            {
                if((entityMask[entityCount] & COMPONENT_VELOCITY) == COMPONENT_NONE)
                    entityMask[entityCount] += COMPONENT_VELOCITY;
                velocityComponent[entityCount] = {0, 0};
            }

            if(!proto["hitbox"].isNil())
            {
                if((entityMask[entityCount] & COMPONENT_HITBOX) == COMPONENT_NONE)
                    entityMask[entityCount] += COMPONENT_HITBOX;
                LuaRef hitbox = proto["hitbox"];
                hitboxComponent[entityCount].xHitbox.width = hitbox["xWidth"].cast<float>();
                hitboxComponent[entityCount].xHitbox.height = hitbox["xHeight"].cast<float>();
                hitboxComponent[entityCount].yHitbox.width = hitbox["yWidth"].cast<float>();
                hitboxComponent[entityCount].yHitbox.height = hitbox["yHeight"].cast<float>();
                hitboxComponent[entityCount].xOffset = {0, hitbox["xOffset"].cast<int>()};
                hitboxComponent[entityCount].yOffset = {hitbox["yOffset"].cast<int>(), 0};
            }

            if(!proto["sprite"].isNil())
            {
                if((entityMask[entityCount] & COMPONENT_SPRITE) == COMPONENT_NONE)
                    entityMask[entityCount] += COMPONENT_SPRITE;
                ///Okay, let's say fuck this for now and just make the animationManager handle all sprite related shit.
                LuaRef sprite = proto["sprite"];
                spriteComponent[entityCount].spritesheet = sprite["spritesheet"].cast<std::string>();
                spriteComponent[entityCount].layer = sprite["layer"].cast<int>();
                //spriteComponent[entityCount].sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
                //spriteComponent[entityCount].layer = proto["sprite"]["layer"].cast<int>();
            }
        }

        ///Then it'll create that type of entity.
        entityCount++;
        entityMask[entityCount] = entityMask[prototype[entityType]] - COMPONENT_PROTOTYPE;

        positionComponent[entityCount] = PositionComponent(positionComponent[prototype[entityType]]);
        velocityComponent[entityCount] = VelocityComponent(velocityComponent[prototype[entityType]]);
        hitboxComponent[entityCount] = HitboxComponent(hitboxComponent[prototype[entityType]]);
        spriteComponent[entityCount] = SpriteComponent(spriteComponent[prototype[entityType]]);
        inputComponent[entityCount] = InputComponent(inputComponent[prototype[entityType]]);
        playerComponent[entityCount] = PlayerComponent(playerComponent[prototype[entityType]]);

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
