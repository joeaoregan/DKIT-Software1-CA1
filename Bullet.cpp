/*
    Bullet.cpp
    Joe O'Regan
    02/10/2022

    Player weapon
*/

#include "Bullet.hpp"
#include <iostream>

const int BULLET_SPEED{10}; // bullet speed

Bullet::Bullet() : GameObject({-50.0f, 360.0f, 50.0f, 5.0f}, "sprites/LaserGreen", true, PLAYER_BULLET)
{
    setSpeed(BULLET_SPEED);
    setActive(false);
}

void Bullet::move()
{
    if (getActive())
    {
        setX(getX() + getSpeed());
    }

    collisions();
}

void Bullet::collisions()
{
    if (getCollision() || getX() >= SCREEN_WIDTH)
    {
        std::cout << "bullet collision" << std::endl;
        setActive(false);
        setX(-getWidth());
        setCollision(false);
    }
    if (getActive())
    {
        setCollisionRect((*getRect())); // update collision rect position if the bullet is active
    }
}

void Bullet::draw()
{
    if (getActive())
    {
        DrawTexturePro(getTexture(), {0, 0, getWidth(), getHeight()}, (*getRect()), {0.0f, 0.0f}, 0.0f, WHITE);
        drawCollisionRect(DEBUG_BULLET);
    }
}
