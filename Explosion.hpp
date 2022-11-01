/*
    Explosion.hpp
    01/11/2022

    Explosion class
    Create explosions for Blood Cells
*/

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "GameObject.hpp"

class Explosion : public GameObject // Explosion inherits directly from the GameObject base class
{
public:
    Explosion();  // constructor
    ~Explosion(); // deconstructor

    void init();       // initialise explosion
    void move();       // update the explosion
    void collisions(); // check for collisions
    void draw();       // render explosion texture
    void destroy();    // clear explosion textures etc. from memory

    Sound fxExplode; // sound to play when explosion occurs
    float runningTime{};
};

#endif