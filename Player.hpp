/*
    Joe O'Regan
    01/10/2022
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

const int NUM_BULLETS = 5;

class Player : public GameObject
{
public:
    Player();
    ~Player();

    void init();
    void move();
    void collisions();
    void draw();
    void destroy();

    Sound fxFire;
    std::vector<GameObject *> bullets;
};

#endif