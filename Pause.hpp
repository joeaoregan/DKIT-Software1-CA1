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
    virtual bool init();                  // initialise level objects
    virtual void handleInput();           // handle user input
    virtual void update(float deltaTime); // update level objects
    virtual void draw();                  // render level objects
    virtual bool close();                 // clear level objects from memory

    virtual game_state getStateID() const { return s_pauseID; } // current state ID (int using enum)

private:
    static const game_state s_pauseID; // identify current state

    GameObject *audioBar;     // Status bar for song current time
    const char *txtSongTitle; // title of current song -- todo dynamically change when song changes
    float musicWidth{0};      // music volume % for status bar
    float fxWidth{0};         // fx volume % for status bar
    float masterWidth{0};     // master volume % for status bar
};

#endif