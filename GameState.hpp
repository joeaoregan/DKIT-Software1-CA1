/*
    GameState.hpp
    20/10/2022

    Base class for Game State
    Level, Menu etc are all child classes
*/

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <iostream>
#include <vector>
#include "GameObject.hpp"
#include "FlashingText.hpp"

// enum to track current state, int more efficient than string, provides readability
enum game_state
{
    MENU = 0,    // start menu state
    LEVEL_1,     // Level 1
    LEVEL_2,     // todo -- implement level 2
    LEVEL_3,     // todo -- implement level 3
    GAME_OVER,   // todo -- implement game over state
    PAUSE,       // pause state
    HIGH_SCORES, // high score state
    EXIT_GAME    // confirm exit state
};

const int INCREMENT = 1;  // for readabiity using function to change selected item up
const int DECREMENT = -1; // for readability using function to change selected item down

class GameState
{
public:
    virtual bool init() = 0;                  // initialise the objects
    virtual void handleInput() = 0;           // handle user input
    virtual void update(float deltaTime) = 0; // update the objects in the state
    // virtual void handleCollisions(){} // todo -- handle collisions for each state
    virtual void draw() = 0;  // render the objects
    virtual bool close() = 0; // clear the objects from memory

    virtual void resume() {} // restart current state -- to do -- necessary?

    virtual game_state getStateID() const = 0; // id of current state (was string, now int using enum)

    void menuOptionChange(int &option, int amount); // change the selected menu option

    inline void setNoBackground(bool bg = true) { m_noBackground = bg; } // set the state having no background
    // bool hasNoBackground() { return m_noBackground; }             // check if the state uses a background -- todo - check is this even needed

protected:
    GameState() : m_loadingComplete(false), m_exiting(false), m_noBackground{false} {} // constructor, initialising variables

    bool m_loadingComplete; // game objects fully loaded
    bool m_exiting;         // leaving the current state

    std::vector<std::string> m_textureIDList;    // Texture IDs for each state
    std::vector<GameObject *> objects;           // list of objects in the current state
    std::vector<GameObject *> selectableObjects; // list of selectable objects (buttons / options)
    std::vector<FlashText *> flashingTextObjs;   // list of flashing text objects in the scene

    int m_menuOption;         // current selected item for menu options in state
    int m_totalMenuItems;     // number of buttons in menu
    int m_totalFlashingItems; // number of flashing text;

    bool m_noBackground;        // state is pushed over another state
    bool targetAcquired{false}; // selectable item availabled
};

#endif