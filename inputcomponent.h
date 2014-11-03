#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "component.h"

/*enum StateType
{
    STATE_NONE,
    STATE_IDLE,
    STATE_IDLE_LEFT,
    STATE_IDLE_RIGHT
};

struct State
{
    std::vector<void (*)()> stateAction;
    std::map<std::string, StateType> stateBranch;
};*/

///Class
class InputComponent : public Component
{
protected:

public:

    /*StateType previousState;
    StateType currentState;
    std::map<StateType, State> *stateMachine;*/

};

#endif


///Really have to sort out how behavior, state and input all interact.
///Single StateMachine per type of creature, state held internally progressing through a singleton machine.
///Input either comes from PlayerInput(InputManager) or AIInput(AIManger)
