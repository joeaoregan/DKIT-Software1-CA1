/*
    Level.cpp
    20/10/2022

    Level state class
    Seperate state for level
*/

#include "Game.hpp"
#include "Constants.hpp"
#include "Level.hpp"
#include "Background.hpp"
#include "BloodCell.hpp"

const int Level::s_levelID = LEVEL_1; // int more efficient than string, enum more readable

int txtScoreWidthCenter; // center the score at top of screen

bool Level::init()
{
    // std::cout << "entering level state" << std::endl;

    GameObject *bg = new Background(); // scrolling background
    objects.push_back(bg);             // add to object list

    for (int i = 0; i < NUM_BLOOD_CELLS; i++) // set the number of blood cell objects in constants header file
    {
        GameObject *bc = new BloodCell(); // create bloodcell
        objects.push_back(bc);            // add to object list
    }

    txtScoreWidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), TextFormat("Score: %08i", Game::Instance()->getScore()), fontSizeHeading, 1).x / 2); // calculate the score center position (done once now, with 8 positions of integer)

    GameState::init(); // initialise the list of objects

    return true; // no errors in initialising -- to do -- check for errors in initialising
}

void Level::update()
{
    GameState::update(); // update the game objects, functionality inherited from GameState
}

void Level::draw()
{
    GameState::draw(); // render the background objects first

    DrawTextEx(Game::Instance()->getFont(), TextFormat("Score: %08i", Game::Instance()->getScore()), {(float)txtScoreWidthCenter, 10.0F}, fontSizeHeading, 1, WHITE); // display the score
    DrawTextEx(Game::Instance()->getFont(), TextFormat("Level: %01i", Game::Instance()->getLevel()), {20.0F, 10.0F}, fontSizeHeading, 1, WHITE);                      // display the current level
}

bool Level::close()
{
    // std::cout << "exiting level state" << std::endl;

    GameState::close(); // clear the objects in the state from memory

    return true; // no errors in exiting -- to do -- check for errors in exiting, or create void function
}