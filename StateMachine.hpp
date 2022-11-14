/*
    StateMachine.cpp
    20/10/2022

    AKA: FSM
    Finite State Machine class
    Handle transition from menu to game play etc.
    singleton
*/

#ifndef STATE_MACHINE_HPP // if state machine not defined already
#define STATE_MACHINE_HPP // of to define

#include "GameState.hpp" // StateMachine manages states

class StateMachine // Finite State Machine class
{
public:                             // public members
    static StateMachine *Instance() // single StateMachine instance throughout game
    {
        if (s_pStateMachine == 0) // if there is no instance
        {
            s_pStateMachine = new StateMachine(); // create one
            return s_pStateMachine;               // use it
        }
        return s_pStateMachine; // otherwise use existing instance
    }

    void push(GameState *pState);   // push a state to the list of states
    void pop();                     // pop the last state (e.g. switching from menu back to level)
    void change(GameState *pState); // change the current state

    void handleInput();           // handle user input
    void update(float deltaTime); // update the objects for the current state
    void draw();                  // render the objects for the current state

    int getID() const; // current state id

private: // private members
    StateMachine() {}

    static StateMachine *s_pStateMachine; // singleton state machine instance

    std::vector<GameState *> m_gameStates; // list of states
};

#endif // end of class definition

typedef StateMachine FSM; // Just can't be bothered typing StateMachine every time