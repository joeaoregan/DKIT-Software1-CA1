/*
    GameState.hpp
    20/10/2022

    Menu state class
    Inherits from GameState
*/

#ifndef MENU_HPP
#define MENU_HPP

#include "GameState.hpp"

class Menu : public GameState // Menu inherits from GameState base class
{
public:
    virtual bool init();                  // initialise menu objects
    virtual void update(float deltaTime); // update menu objects
    virtual void draw();                  // render menu objects
    virtual bool close();                 // clear menu objects from memory

    virtual int getStateID() const { return s_menuID; } // identifies current state

    std::vector<GameObject *> selectableObjects; // list of selectable objects (buttons / options)

private:
    static const int s_menuID; // id for current state
    int m_menuOption;          // current selected menu option
};

#endif