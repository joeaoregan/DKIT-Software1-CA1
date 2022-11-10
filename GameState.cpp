/*
    GameState.cpp
    20/10/2022

    Game State class
    Base class for game state classes
*/

#include "GameState.hpp"

bool GameState::init()
{
    m_totalMenuItems = 0;
    m_totalFlashingItems = 0;

    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).init(); // initialise the object
    }

    return true; // return true if no errors (possibly no need if no raylib functions causing errors)
}

void GameState::update(float deltaTime)
{
    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).move(); // update the object
    }
}

void GameState::draw()
{
    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).draw(); // render the object
    }
}

bool GameState::close()
{
    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).destroy(); // clear object from memory
    }

    return true;
}

void GameState::menuOptionChange(int &option, int amount)
{
    option += amount;

    if (option > m_totalMenuItems - 1)
    {
        option = 0;
    }
    else if (option < 0)
    {
        option = m_totalMenuItems - 1;
    }
}