/*
    StateMachine.cpp
    20/10/2022

    Finite State Machine class
    Handle transition from menu to game play etc.
*/

#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "GameState.hpp"

class StateMachine // Finite State Machine class
{
public:
    void push(GameState *pState);   // push a state to the list of states
    void pop();                     // pop the last state (e.g. switching from menu back to level)
    void change(GameState *pState); // change the current state

    void update(); // update the objects for the current state
    void draw();   // render the objects for the current state

    // std::vector<GameState *> &getGameStates() { return m_gameStates; }

private:
    std::vector<GameState *> m_gameStates; // list of states
};

#endif