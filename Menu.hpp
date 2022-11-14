/*
    GameState.hpp
    20/10/2022

    Menu state class
    Inherits from GameState
*/

#ifndef MENU_HPP // if the menu class isn't defined already
#define MENU_HPP // ensure header file only processed once

#include "GameState.hpp" // parent class header

class Menu : public GameState // Menu inherits from GameState base class
{
public:                                   // public variables accessible everywhere
    virtual bool init();                  // initialise menu objects
    virtual void handleInput();           // handle user input
    virtual void update(float deltaTime); // update menu objects
    virtual void draw();                  // render menu objects
    virtual bool close();                 // clear menu objects from memory

    virtual game_state getStateID() const { return s_menuID; } // identifies current state

private:                              // private variables accessible only from this class
    static const game_state s_menuID; // id for current state
};                                    // end of class

#endif // end of class definition