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

// enum to track current state, int more efficient than string, provides readability
enum game_states
{
    MENU = 0,
    LEVEL_1 = 1,
    LEVEL_2 = 2,
    LEVEL_3 = 3,
    GAME_OVER = 4,
    PAUSE = 5
};

class GameState
{
public:
    virtual bool init() = 0;                  // initialise the objects
    virtual void update(float deltaTime) = 0; // update the objects in the state
    virtual void draw() = 0;                  // render the objects
    virtual bool close() = 0;                 // clear the objects from memory

    virtual void resume() {} // restart current state -- to do -- necessary?

    virtual int getStateID() const = 0; // id of current state (was string, now int using enum)

    std::vector<GameObject *> objects; // list of objects in the current state

protected:
    GameState() : m_loadingComplete(false), m_exiting(false) {} // constructor, initialising variables

    bool m_loadingComplete; // game objects fully loaded
    bool m_exiting;         // leaving the current state

    std::vector<std::string> m_textureIDList; // Texture IDs for each state
};

#endif