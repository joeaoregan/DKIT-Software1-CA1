/*
    StateMachine.cpp
    20/10/2022

    Finite State Machine class
    Handle transitions between game states
*/

#include "StateMachine.hpp"

// void StateMachine::clean()
// {
//     if (!m_gameStates.empty())
//     {
//         m_gameStates.back()->onExit();

//         delete m_gameStates.back();

//         m_gameStates.clear();
//     }
// }

void StateMachine::update(float deltaTime)
{
    if (!m_gameStates.empty())
    {
        m_gameStates.back()->update(deltaTime); // If there is a state update it
    }
}

void StateMachine::draw()
{
    if (!m_gameStates.empty())
    {                                // Check if there is any state in the states list
        m_gameStates.back()->draw(); // Render existing states
    }
}

/* Push the passed-in pState parameter into the m_gameStates array &
call its onEnter() */
void StateMachine::push(GameState *pState)
{
    // std::cout << "before push - m_gameStates size: " << m_gameStates.size() << std::endl;

    m_gameStates.push_back(pState); // Add state to the states list
    m_gameStates.back()->init();    // init the state

    // std::cout << "after push - m_gameStates size: " << m_gameStates.size() << std::endl;
}

/* Check if there's states available to remove, & if there is,
call onExit() of the current state clearing it from memory, then remove it */
void StateMachine::pop()
{
    if (!m_gameStates.empty())
    { // If the vector of stored states is not empty
        // delete m_gameStates.back();
        m_gameStates.back()->close(); // Call close() to clear the state
        m_gameStates.pop_back();      // Remove current state
    }

    // m_gameStates.back()->resume();
}

/* Check if there are states in the array, do nothing if the state matches the
current stored states ID. If its not a match remove the current state, add the new
state, call its onEnter() */
void StateMachine::change(GameState *pState)
{
    if (!m_gameStates.empty())
    { // If the vector of states is not empty
        if (m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return; // If the state is the same as the one stored do nothing
        }

        // delete m_gameStates.back();
        m_gameStates.back()->close(); // Clear the previous state
        m_gameStates.pop_back();      // Remove it
    }

    // pState->init(); // Initialise new state

    m_gameStates.push_back(pState); // Push back new state
    m_gameStates.back()->init();    // init new state
}

// get the id of the current state
int StateMachine::getID()
{
    return m_gameStates.back()->getStateID();
}