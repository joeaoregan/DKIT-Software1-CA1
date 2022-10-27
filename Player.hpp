/*
    Player.hpp
    Joe O'Regan
    01/10/2022

    Player spaceship game object
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

const int NUM_BULLETS = 5; // The player currently has 5 bullets -- to do -- make this a power up

class Player : public GameObject // Player inherits directly from the GameObject base class
{
public:
    Player();  // constructor
    ~Player(); // deconstructor

    void init();       // initialise player
    void move();       // update the player
    void collisions(); // check for collisions, reduce health, etc.
    void draw();       // render player texture
    void destroy();    // clear player textures etc. from memory

    Sound fxFire;                      // sound to play when bullet fires
    std::vector<GameObject *> bullets; // list of bullet objects to update rendering etc.

    int flash = 255;           // Start with green and blue values as 255
    int direction = 1;         // change colour up and down by making this postive / negative value and multiplying
    const int flashSpeed = 20; // increment flashing by this amount each frame
    const int flashTimes = 5;  // number of times to flash player
    int flashCount = 1;        // number of times player has flashed

private:
    void handleInput(); // handle input for player
};

#endif