#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
/*#include "component.h"
#include "positioncomponent.h"
#include "velocitycomponent.h"
#include "hitboxcomponent.h"
#include "spritecomponent.h"*/
///#include "world.h"

//static const int MAX_ENTITY_COUNT = 128;

/*enum ComponentType
{
    COMPONENT_NONE = 0,
    COMPONENT_POSITION = 1,
    COMPONENT_VELOCITY = 2,
    COMPONENT_HITBOX = 4,
    COMPONENT_SPRITE = 8,
    COMPONENT_INPUT = 16
};*/

///Class
class AssetManager
{
protected:

public:

    //std::vector<sf::Texture> loadedTexture;
    std::map<std::string, sf::Texture> loadedTexture;
    std::map<std::string, sf::Font> loadedFont;

    AssetManager(){};

    //void loadAsset();
    void loadTexture(std::string textureFile);
    void loadFont(std::string fontFile);
    /*void addEntity(int entityType); ///Here, int will be the "entityType." Which will be determined from the streamed world info.
    void removeEntity(int ID);
    void removeAllEntities();
    void addComponent(int ID, ComponentType componentType);
    void removeComponent(int ID, ComponentType componentType);*/

    //void printEntities();
    //void createEntity(World& world, std::string entityType);

};

#endif

