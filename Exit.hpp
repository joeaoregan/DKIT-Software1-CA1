/*
    Exit.hpp
    12/11/2022

    Exit confirmation state
    display 2 buttons asking to confirm quitting game
*/

#ifndef EXIT_HPP
#define EXIT_HPP

#include "GameState.hpp"

class Exit : public GameState
{
public:
    virtual bool init();                  // initialise objects
    virtual void handleInput();           // handle user input
    virtual void update(float deltaTime); // update objects
    virtual void draw();                  // render objects
    virtual bool close();                 // clear objects from memory

    virtual game_state getStateID() const { return s_exitID; } // current state ID (int using enum)

private:
    static const game_state s_exitID; // identify current state
};

#endif