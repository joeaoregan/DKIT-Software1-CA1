/*
    Pause.hpp
    02/11/2022

    Pause state class
    Handle the Pause state
    display buttons to resume or exit game
    displays sliders for adjusting audio volumes
    displays status bar with current song track length
    can enter Exit state or resume Play state from here
*/

#ifndef PAUSE_HPP // if Pause class not defined already
#define PAUSE_HPP // ok to define Pause class

#include "GameState.hpp" // base class header file

class Pause : public GameState // Pause is a sub class of GameState
{
public:                                   // publicly accessible members
    virtual bool init();                  // initialise level objects
    virtual void handleInput();           // handle user input
    virtual void update(float deltaTime); // update level objects
    virtual void draw();                  // render level objects
    virtual bool close();                 // clear level objects from memory

    virtual game_state getStateID() const { return s_pauseID; } // current state ID (int using enum)

private:                               // private members accessible only this class
    static const game_state s_pauseID; // identify current state

    GameObject *audioBar;     // Status bar for song current time
    const char *txtSongTitle; // title of current song -- todo dynamically change when song changes
    float musicWidth{0};      // music volume % for status bar
    float fxWidth{0};         // fx volume % for status bar
    float masterWidth{0};     // master volume % for status bar
};                            // end of class

#endif // end of class definition