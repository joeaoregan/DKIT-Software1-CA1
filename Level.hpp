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
    bool checkCollision(Rectangle *a, Rectangle *b);

    virtual bool init();   // initialise level objects
    virtual void update(); // update level objects
    virtual void draw();   // render level objects
    virtual bool close();  // clear level objects from memory

    virtual int getStateID() const { return s_levelID; } // current state ID (int using enum)

    GameObject *player;

    std::vector<GameObject *> niceList;
    std::vector<GameObject *> naughtyList;

private:
    static const int s_levelID; // identify current state
};

#endif