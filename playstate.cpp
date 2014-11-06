#include "playstate.h"

void PlayState::init()
{
    //assetManager.loadTexture("oasisnewhood.png");
    assetManager.loadTexture("grass_tile_test.png");
    assetManager.loadTexture("arrows.png");
    assetManager.loadFont("VeraMono.ttf");

    ///THIS NONSENSE IS JUST DEBUGGING----------------------------------------*/
    eManager.addEntity();
    eManager.addComponent(0, COMPONENT_POSITION);
    eManager.addComponent(0, COMPONENT_VELOCITY);
    eManager.addComponent(0, COMPONENT_HITBOX);
    eManager.addComponent(0, COMPONENT_SPRITE);
    eManager.addComponent(0, COMPONENT_INPUT);
    eManager.positionComponent[0] = {0, 129};

    eManager.spriteComponent[0].sprite.setTexture(assetManager.getTexture("oasisnewhood.png"));
    //eManager.spriteComponent[0].sprite.setTexture(assetManager.loadedTexture["oasisnewhood.png"]);

    eManager.spriteComponent[0].sprite.setTextureRect(sf::IntRect(0,0, 19, 55));
    eManager.spriteComponent[0].layer = 0;
    eManager.velocityComponent[0].velocity = {0.f, 0.f};
    eManager.hitboxComponent[0].xOffset = {-3, 11};
    eManager.hitboxComponent[0].yOffset = {1, 0};
    eManager.hitboxComponent[0].xHitbox.width = 25;
    eManager.hitboxComponent[0].xHitbox.height = 23;
    eManager.hitboxComponent[0].yHitbox.width = 20;
    eManager.hitboxComponent[0].yHitbox.height = 56;

    debug.setFont(assetManager.loadedFont["VeraMono.ttf"]);
    //debug.setString("Position: " + eManager.positionComponent[0].position.x + "," + eManager.positionComponent[0].position.y);
    debug.setCharacterSize(24);
    debug.setColor(sf::Color::Cyan);
    debug.setPosition(2, 334);

    /*eManager.addEntity();
    eManager.addComponent(1, COMPONENT_POSITION);
    eManager.addComponent(1, COMPONENT_VELOCITY);
    eManager.addComponent(1, COMPONENT_SPRITE);
    eManager.addComponent(1, COMPONENT_HITBOX);
    eManager.spriteComponent[1].sprite.setTexture(assetManager.loadedTexture["arrows.png"]);
    eManager.spriteComponent[1].sprite.setTextureRect(sf::IntRect(0,0, 31, 31));
    eManager.spriteComponent[1].layer = 0;
    eManager.positionComponent[1].position = {50, 50};
    eManager.hitboxComponent[1].xHitbox.width = 32.f;
    eManager.hitboxComponent[1].xHitbox.height = 32.f;
    eManager.hitboxComponent[1].yHitbox.width = 32.f;
    eManager.hitboxComponent[1].yHitbox.height = 32.f;
    */
    while(eManager.entityCount < 20)
    {
        eManager.addEntity();
        eManager.addComponent(eManager.entityCount, COMPONENT_POSITION);
        //eManager.addComponent(eManager.entityCount, COMPONENT_VELOCITY);
        eManager.addComponent(eManager.entityCount, COMPONENT_SPRITE);
        eManager.addComponent(eManager.entityCount, COMPONENT_HITBOX);
        eManager.spriteComponent[eManager.entityCount].sprite.setTexture(assetManager.loadedTexture["grass_tile_test.png"]);
        eManager.spriteComponent[eManager.entityCount].sprite.setTextureRect((eManager.entityCount%3 == 0 ? sf::IntRect(0, 32, 32, 32) : sf::IntRect(32,32,32,32)));
        eManager.spriteComponent[eManager.entityCount].layer = 0;
        eManager.positionComponent[eManager.entityCount].position = {eManager.entityCount*32.f, 200.f};
        if(eManager.entityCount == 2)
        {
            eManager.addComponent(eManager.entityCount, COMPONENT_VELOCITY);
            eManager.positionComponent[eManager.entityCount].position = {32, 32};
            eManager.velocityComponent[eManager.entityCount].velocity = {32.f, 32.f};
        }
        eManager.hitboxComponent[eManager.entityCount].xHitbox.width = 32.f;
        eManager.hitboxComponent[eManager.entityCount].xHitbox.height = 28.f;
        eManager.hitboxComponent[eManager.entityCount].yHitbox.width = 28.f;
        eManager.hitboxComponent[eManager.entityCount].yHitbox.height = 32.f;
        eManager.hitboxComponent[eManager.entityCount].xOffset = {0, 2};
        eManager.hitboxComponent[eManager.entityCount].yOffset = {2, 0};
    }
    while(eManager.entityCount < 40)
    {
        eManager.addEntity();
        eManager.addComponent(eManager.entityCount, COMPONENT_POSITION);
        eManager.addComponent(eManager.entityCount, COMPONENT_SPRITE);
        eManager.spriteComponent[eManager.entityCount].sprite.setTexture(assetManager.loadedTexture["grass_tile_test.png"]);
        eManager.spriteComponent[eManager.entityCount].sprite.setTextureRect((eManager.entityCount%5 == 0 ? sf::IntRect(32, 0, 32, 32) : sf::IntRect(0,0,32,32)));
        eManager.spriteComponent[eManager.entityCount].layer = 1;
        eManager.positionComponent[eManager.entityCount].position = {(eManager.entityCount-20)*32.f, 200.f-32.f};
    }

    /*eManager.addEntity("test_entity1");
    if(!((*eManager.prototype["test_entity2"]).isNil()))
    eManager.spriteComponent[eManager.entityCount].sprite.setTexture(assetManager.loadedTexture[((*eManager.prototype["test_entity1"])["sprite"]["spritesheet"].cast<std::string>())]);
    */
    /*eManager.addEntity();
    eManager.addComponent(2, COMPONENT_POSITION);
    eManager.addComponent(2, COMPONENT_VELOCITY);
    eManager.addComponent(2, COMPONENT_SPRITE);
    eManager.addComponent(2, COMPONENT_HITBOX);
    eManager.spriteComponent[2].sprite.setTexture(assetManager.loadedTexture["arrows.png"]);
    eManager.spriteComponent[2].sprite.setTextureRect(sf::IntRect(0,0, 31, 31));
    eManager.spriteComponent[2].layer = 0;
    eManager.positionComponent[2].position = {18, 82};
    eManager.hitboxComponent[2].xHitbox.width = 32.f;
    eManager.hitboxComponent[2].xHitbox.height = 32.f;
    eManager.hitboxComponent[2].yHitbox.width = 32.f;
    eManager.hitboxComponent[2].yHitbox.height = 32.f;*/
    /*
    eManager.addEntity();
    eManager.addComponent(2, COMPONENT_POSITION);
    eManager.addComponent(2, COMPONENT_VELOCITY);
    eManager.addComponent(2, COMPONENT_SPRITE);
    eManager.spriteComponent[2].sprite.setTexture(arrows);
    eManager.spriteComponent[2].layer = 0;
    eManager.positionComponent[2].position = {80, 150};
    //world.velocityComponent[0]->velocity.x = 0.001;*/

    if(eManager.worldChanged)
    {
        moveSys.registerEntities(eManager);
        collSys.registerEntities(eManager);
        drawSys.registerEntities(eManager);
        eManager.worldChanged = false;
    }

    debugManager = DebugManager(&eManager, &assetManager);
}

void PlayState::cleanUp()
{
    eManager.removeAllEntities();
}

void PlayState::pause()
{

}

void PlayState::resume()
{

}

void PlayState::handleEvents(GameEngine *game)
{
    inManager.update();
    eManager.velocityComponent[0].velocity.x = 0;
    //eManager.velocityComponent[0].velocity.y += 9.f;
    if(inManager.isInput(INPUT_LEFT))
    {
        eManager.spriteComponent[0].sprite.setTextureRect(sf::IntRect(0,0, 20, 56));
        eManager.velocityComponent[0].velocity.x = -32.f*4.f;
    }
    if(inManager.isInput(INPUT_RIGHT))
    {
        eManager.spriteComponent[0].sprite.setTextureRect(sf::IntRect(21, 0, 20, 56));
        eManager.velocityComponent[0].velocity.x = 32.f*4.f;
    }
    if(inManager.isKeyPressed(INPUT_JUMP))
        eManager.velocityComponent[0].velocity.y = -32.f*7.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
        debugManager.toggle();
    /*for(int ID = 0; ID < eManager.entityCount; ID++)
    {
        if((eManager.entityMask[ID] & COMPONENT_INPUT))
        {
            if(inManager.isInput(INPUT_LEFT))
                world.velocityComponent[ID]->velocity.x += -0.01;
            if(inManager.isInput(INPUT_RIGHT))
                world.velocityComponent[ID]->velocity.x += 0.01;
            if(inManager.isInput(INPUT_JUMP))
                world.velocityComponent[ID]->velocity.y += 0.01;
        }
    }*/
}

void PlayState::update(GameEngine *game, float dt)
{
    eManager.velocityComponent[0].velocity.y += 32.f*9.f*dt;

    moveSys.update(dt);
    collSys.update();
    if(debugManager.isActive())
    {
        debugManager.update();
    }
}

void PlayState::draw(GameEngine *game)
{
    ///This easy code here centers the camera on the player
    ///Need to implement more cleanly and actually center on the player (rather than the top-left)
    ///Also needs to be a little contextual.
    /*sf::View camera = game->window.getDefaultView();
    camera.setCenter(eManager.positionComponent[0].position);
    game->window.setView(camera);*/
    game->window.clear(sf::Color::Magenta);
    drawSys.draw(game->window);
    if(debugManager.isActive())
        debugManager.draw(game->window);
    game->window.display();
}
