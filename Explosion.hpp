/*
    Explosion.hpp
    01/11/2022

    Explosion class
    Create explosions for Blood Cells
*/

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "GameObject.hpp" // Game Object parent class header file

const bool DEBUG_EXPLOSION = true; // debug flag for explosion objects

class Explosion : public GameObject // Explosion inherits directly from the GameObject base class
{
public:
    Explosion(Vector2 position); // constructor
    ~Explosion();                // deconstructor

    void init() {}       // initialise explosion
    void move();         // update the explosion
    void collisions() {} // check for collisions
    void draw();         // render explosion texture
    void destroy();      // clear explosion textures etc. from memory

    Sound fxExplode;     // sound to play when explosion occurs
    float runningTime{}; // how often to increment the frame
};

#endif