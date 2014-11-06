#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "parser.h"

static const int NUM_OF_INPUTS = 12;
static const int BUFFER_SIZE = 32;

enum InputType
{
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_INTERACT,
    INPUT_JUMP,
    INPUT_GUARD,
    INPUT_ATTACK,
    INPUT_SPECIAL,
    INPUT_DASH,
    INPUT_START,
    INPUT_SELECT
};

/*struct TimedInput
{
    InputType inputType;
    sf::Time life;
};*/

///Class
class InputManager
{
protected:

    sf::Keyboard::Key inputBinding[NUM_OF_INPUTS];
    bool inputRegister[NUM_OF_INPUTS];
    bool keyPressed[NUM_OF_INPUTS];
    bool keyReleased[NUM_OF_INPUTS];

public:

    InputManager();

    void update();
    bool isInput(InputType inputType){return inputRegister[inputType];}
    bool isKeyPressed(InputType inputType){return keyPressed[inputType];}
    bool isKeyReleased(InputType inputType){return keyReleased[inputType];}

};

#endif

