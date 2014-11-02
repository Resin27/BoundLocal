#include "inputmanager.h"

InputManager::InputManager()
{
    Parser parser("config.lua");
    //parser.openFile("config.txt");
    //parser.parseFileSection("config.txt", "Control");
    //parser.closeFile();

    inputBinding[INPUT_UP] = parser.getKey("control", "up");
    inputBinding[INPUT_DOWN] = parser.getKey("control", "down");
    inputBinding[INPUT_LEFT] = parser.getKey("control", "left");
    inputBinding[INPUT_RIGHT] = parser.getKey("control", "right");
    inputBinding[INPUT_INTERACT] = parser.getKey("control", "interact");
    inputBinding[INPUT_JUMP] = parser.getKey("control", "jump");
    inputBinding[INPUT_GUARD] = parser.getKey("control", "guard");
    inputBinding[INPUT_ATTACK] = parser.getKey("control", "attack");
    inputBinding[INPUT_SPECIAL] = parser.getKey("control", "special");
    inputBinding[INPUT_DASH] = parser.getKey("control", "dash");
    inputBinding[INPUT_START] = parser.getKey("control", "start");
    inputBinding[INPUT_SELECT] = parser.getKey("control", "select");

    //~Parser();

    /*inputBinding[INPUT_UP] = sf::Keyboard::Key::Up;
    inputBinding[INPUT_DOWN] = sf::Keyboard::Key::Down;
    inputBinding[INPUT_LEFT] = sf::Keyboard::Key::Left;
    inputBinding[INPUT_RIGHT] = sf::Keyboard::Key::Right;
    inputBinding[INPUT_INTERACT] = sf::Keyboard::Key::Z;
    inputBinding[INPUT_JUMP] = sf::Keyboard::Key::Space;
    inputBinding[INPUT_GUARD] = sf::Keyboard::Key::A;
    inputBinding[INPUT_ATTACK] = sf::Keyboard::Key::S;
    inputBinding[INPUT_SPECIAL] = sf::Keyboard::Key::D;
    inputBinding[INPUT_DASH] = sf::Keyboard::Key::F;
    inputBinding[INPUT_START] = sf::Keyboard::Key::Return;
    inputBinding[INPUT_SELECT] = sf::Keyboard::Key::BackSpace;*/


    for(int i = 0; i < NUM_OF_INPUTS; i++)
        inputRegister[i] = false;
}

void InputManager::update()
{
    for(int i = 0; i < NUM_OF_INPUTS; i++)
    {
        /*if(!inputRegister[i] && sf::Keyboard::isKeyPressed(inputBinding[i]))
        {
            for(int j = BUFFER_SIZE; j > 0; j--)
            {
                inputBuffer[j] = inputBuffer[j-1];
            }
            inputBuffer[0] = TimedInput{InputType(i), sf::Time()};
        }*/
        ///Really need to implement a sort of edge-triggering register, so make sure that button presses are only counted once.
        bool keyState = sf::Keyboard::isKeyPressed(inputBinding[i]);
        keyPressed[i] = false;
        keyReleased[i] = false;
        if(!inputRegister[i] && keyState)
        {
            keyPressed[i] = true;
        }
        if(inputRegister[i] && !keyState)
        {
            keyReleased[i] = true;
        }
        inputRegister[i] = keyState;
    }
    /*for(int i = 0; i < BUFFER_SIZE; i++)
        std::cout << inputBuffer[i].inputType;
    std::cout << "\n";*/
}
