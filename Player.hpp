/*
    Player.hpp
    Joe O'Regan
    01/10/2022

    Player spaceship game object
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

const bool TEST_PLAYER = true;
const float HEALTH_TOTAL = 100.0f;

const int LASER_FIRE_RATE = 20; // time until next laser blast
const int NUM_BULLETS = 5;      // The player currently has 5 bullets -- to do -- make this a power up

const int FLASH_SPEED = 20; // increment flashing by this amount each frame
const int FLASH_TIMES = 5;  // number of times to flash player

class Player : public GameObject // Player inherits directly from the GameObject base class
{
public:
    Player();    // constructor
    ~Player() {} // deconstructor

    void init();       // initialise player
    void move();       // update the player
    void collisions(); // check for collisions, reduce health, etc.
    void draw();       // render player texture
    void destroy();    // clear player textures etc. from memory

    bool isFlashing() { return m_flashing; }
    void setFlashing(bool flash) { m_flashing = flash; }

    void setHealth(int health);

private:
    void handleInput(); // handle input for player

    int m_laserFireCount; // current time until next laser fire
    Sound m_fxFire;       // sound to play when bullet fires

    bool m_flashing;
    int m_flashDirection;   // change colour up and down by making this postive / negative value and multiplying
    int m_flashCount;       // number of times player has flashed
    int m_flashColourValue; // Start with green and blue values as 255

    GameObject *m_healthBar; // Status bar for player health
};

#endif