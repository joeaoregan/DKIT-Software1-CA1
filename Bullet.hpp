/*
    Joe O'Regan
    02/10/2022
*/

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "GameObject.hpp"

class Bullet : public GameObject
{
public:
    Bullet();
    ~Bullet();

    void init();
    void move();
    void collisions();
    void draw();
    void destroy();
};

#endif