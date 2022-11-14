/*
    Bullet.hpp
    Joe O'Regan
    02/10/2022

    Player weapon
*/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp" // Game Object parent class header file

const bool DEBUG_BULLET = true;

class Bullet : public GameObject // child of GameObject base class
{
public:
    Bullet();    // constructor
    ~Bullet() {} // deconstructor -- todo implement this

    void init() {}     // initialise bullet object -- todo figure out do I need this, probably do for resetting the level
    void move();       // update the bullet object
    void collisions(); // check collisions with other objects
    void draw();       // render bullet object
    void destroy() {}  // clear bullet object from memory
};

#endif