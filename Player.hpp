/*
    Joe O'Regan
    01/10/2022
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player();
    ~Player();

    void move();
    void collisions();
    void draw();
};

#endif