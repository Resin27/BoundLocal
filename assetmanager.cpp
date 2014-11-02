#include "assetmanager.h"

void AssetManager::loadTexture(std::string textureFile)
{
    //loadedTexture.push(sf::Texture);
    if(!loadedTexture[textureFile].loadFromFile(textureFile))
        std::cout << "Whoops!" << std::endl;
}

void AssetManager::loadFont(std::string fontFile)
{
    if(!loadedFont[fontFile].loadFromFile(fontFile))
        std::cout << "Whoops!" << std::endl;
}
