/*
    Bullet.hpp
    Joe O'Regan
    02/10/2022

    Player weapon
*/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"

class Bullet : public GameObject // child of GameObject base class
{
public:
    Bullet();  // constructor
    ~Bullet(); // deconstructor

    void init();       // initialise bullet object
    void move();       // update the bullet object
    void collisions(); // check collisions with other objects
    void draw();       // render bullet object
    void destroy();    // clear bullet object from memory
};

#endif