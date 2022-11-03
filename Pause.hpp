/*
    Pause.hpp
    02/11/2022

    Pause state class
    Handle the Pause state
*/

#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "GameState.hpp"

class Pause : public GameState
{
public:
    virtual bool init();   // initialise level objects
    virtual void update(); // update level objects
    virtual void draw();   // render level objects
    virtual bool close();  // clear level objects from memory

    virtual int getStateID() const { return s_pauseID; } // current state ID (int using enum)

private:
    static const int s_pauseID; // identify current state

    const char *txtPause;

    int txtPauseCenter;
};

#endif