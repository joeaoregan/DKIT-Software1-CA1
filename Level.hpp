/*
    Level.hpp
    20/10/2022

    Level state class
    Handle the level state
*/

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "GameState.hpp"

class Level : public GameState
{
public:
    bool checkCollision(Rectangle *a, Rectangle *b); // check collisions between objects -- todo - find a better place for this function

    virtual bool init();                  // initialise level objects
    virtual void handleInput();           // handle user input NOT NEEDED HERE
    virtual void update(float deltaTime); // update level objects
    virtual void draw();                  // render level objects
    virtual bool close();                 // clear level objects from memory

    virtual game_state getStateID() const { return s_levelID; } // current state ID (int using enum)

    GameObject *player; // Player object

    std::vector<GameObject *> niceList;    // player objects, bullets etc
    std::vector<GameObject *> naughtyList; // enemy objects and stuff player can collide with

private:
    static const game_state s_levelID; // identify current state
};

#endif