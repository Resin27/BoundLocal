#include "controlsystem.h"

/*void RenderSystem::draw(sf::RenderWindow& window, PositionComponent *positionComponent, SpriteComponent *spriteComponent)

    spriteComponent->sprite.setPosition(positionComponent->position);
    window.draw(spriteComponent->sprite);
}*/

/*void ControlSystem::lookLeft()
{
    std::cout << "looked left" << std::endl;
}

void ControlSystem::lookRight()
{
    std::cout << "looked right" << std::endl;

}

void ControlSystem::ControlSystem()
{
    State idleLeft;
    idleLeft.stateAction.push_back(&lookLeft);
    idleLeft.stateBranch["input right"] = STATE_IDLE_RIGHT;
    State idleRight;
    idleRight.stateAction.push_back(&lookRight);
    idleRight.stateBranch["input left"] = STATE_IDLE_LEFT;

    //testStateMachine[STATE_NONE] = State{doNothing(), stateBranch["input left"] = testStateMachine[STATE_IDLE_LEFT]};
}*/

void ControlSystem::registerEntities(EntityManager& eManager)
{
    playerRegister.clear();
    playerInputRegister.clear();
    //aiRegister.clear();
    //aiInputRegister.clear();
    for(int entityID = 0; entityID < eManager.entityCount; entityID++)
    {
        if((eManager.entityMask[entityID] & (COMPONENT_PLAYER | COMPONENT_INPUT)) != (COMPONENT_PLAYER | COMPONENT_INPUT))
        {
            playerRegister.push_back(&(eManager.playerComponent[entityID]));
            playerInputRegister.push_back(&(eManager.inputComponent[entityID]));
        }
        ///For when AIComponents are introduced.
        /*else if((eManager.entityMask[entityID] & (COMPONENT_AI | COMPONENT_INPUT)) != COMPONENT_NONE)
        {
            aiRegister.push_back(&(eManager.aiComponent[entityID]));
            aiInputRegister.push_back(&(eManager.inputComponent[entityID]));
        }*/
    }
}

/*void RenderSystem::draw(sf::RenderWindow& window)
{
    for(unsigned int i = 0; i < positionRegister.size(); i++)
    {
        spriteRegister[i]->sprite.setPosition(positionRegister[i]->position);
        window.draw(spriteRegister[i]->sprite);
    }
}*/

/*void ControlSystem::doNothing()
{

}*/

void ControlSystem::update()//EntityManager &eManager)
{

}
