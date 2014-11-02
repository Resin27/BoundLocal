#include "debugmanager.h"

DebugManager::DebugManager(EntityManager* entityManager, AssetManager* assetManager)
{
    focusEntity = 0;
    active = false;
    eManager = entityManager;
    aManager = assetManager;
    text.setFont(aManager->loadedFont["VeraMono.ttf"]);
    text.setCharacterSize(12);
    text.setColor(sf::Color::Cyan);
}

void DebugManager::update()
{
    entityData.clear();
    std::ostringstream convert;
    convert.str(std::string());
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        focusEntity++;
        if(focusEntity == eManager->entityCount)
            focusEntity = 0;
    }
        std::string tempText;
        convert.str(std::string());
        convert << focusEntity;
        tempText = convert.str();
        text.setString("Entity: " + tempText);
        entityData.push_back(text);

    if((eManager->entityMask[focusEntity] & COMPONENT_POSITION) == COMPONENT_POSITION)
    {
        std::string tempText;
        convert.str(std::string());
        convert << int(eManager->positionComponent[focusEntity].position.x) << "," << int(eManager->positionComponent[focusEntity].position.y);
        tempText = convert.str();
        text.setString("Position: " + tempText);
        entityData.push_back(text);
    }
    if((eManager->entityMask[focusEntity] & COMPONENT_VELOCITY) == COMPONENT_VELOCITY)
    {
        std::string tempTest;
        convert.str(std::string());
        convert << int(eManager->velocityComponent[focusEntity].velocity.x) << "," << int(eManager->velocityComponent[focusEntity].velocity.y);
        tempTest = convert.str();
        text.setString("Velocity: " + tempTest);
        entityData.push_back(text);
    }
}

void DebugManager::draw(sf::RenderWindow& window)
{
    for(unsigned int i = 0; i < entityData.size(); i++)
    {
        entityData[i].setPosition(2, 2 + i*16);
        window.draw(entityData[i]);
    }
}
