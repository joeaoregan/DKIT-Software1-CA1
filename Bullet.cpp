/*
    Bullet.cpp
    Joe O'Regan
    02/10/2022

    Player weapon
*/

#include "Bullet.hpp"
#include <iostream>

const int BULLET_SPEED{10};

Bullet::Bullet() : GameObject({-50.0f, 360.0f, 50.0f, 5.0f}, "sprites/LaserGreen", true)
{
    setSpeed(BULLET_SPEED);
    setActive(false);
    setID(BULLET);
}

Bullet::~Bullet()
{
}

void Bullet::init()
{
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
}

void Bullet::draw()
{
    if (getActive())
    {
        DrawTexturePro(getTexture(), {0, 0, (float)getWidth(), (float)getHeight()}, {getX(), getY(), (float)getWidth(), (float)getHeight()}, {0.0f, 0.0f}, 0.0f, WHITE);

        if (TEST_BULLET)
        {
            // Bounding box to check collisions
            DrawRectangleLines(getX(), getY(), getWidth(), getHeight(), WHITE);
        }
    }
}

void Bullet::destroy() {}