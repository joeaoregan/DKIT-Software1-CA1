/*
    Player.hpp
    Joe O'Regan
    01/10/2022

    Player spaceship game object
*/

#ifndef PLAYER_HPP // if player class not defined
#define PLAYER_HPP // ok to define player class

#include "GameObject.hpp" // include base class header

const bool DEBUG_PLAYER = true; // show messages, bounding boxes etc

const float HEALTH_TOTAL = 100.0f; // health expressed as percentage for status bars
const int LASER_FIRE_RATE = 20;    // time until next laser blast
const int NUM_BULLETS = 5;         // The player currently has 5 bullets -- to do -- make this a power up
const int FLASH_SPEED = 20;        // increment flashing by this amount each frame
const int FLASH_TIMES = 5;         // number of times to flash player
const int PLAYER_PARTICLES = 15;   // number of particles to render for engine emission

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

    inline bool isFlashing() const { return m_flashing; }       // check is the player flashing after a collision
    inline void setFlashing(bool flash) { m_flashing = flash; } // set the player flashing or not

    void setHealth(int health); // set the health and update health status bar

private:
    void handleInput();   // handle input for player
    void drawParticles(); // draw ship engine particles

    int m_laserFireCount; // current time until next laser fire
    Sound m_fxFire;       // sound to play when bullet fires

    bool m_flashing;        // player is flashing after collision
    int m_flashDirection;   // change colour up and down by making this postive / negative value and multiplying
    int m_flashCount;       // number of times player has flashed
    int m_flashColourValue; // Start with green and blue values as 255

    Texture2D red, green, blue, shimmer; // textures for random rgb particles used in ship engine

    GameObject *m_healthBar;                 // Status bar for player health
    GameObject *particles[PLAYER_PARTICLES]; // list of particles, with amount set by constant above
};                                           // end of class

#endif // end of class header