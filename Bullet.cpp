/*
    Bullet.cpp
    Joe O'Regan
    02/10/2022

    Player weapon
*/

#include "Bullet.hpp"

const int BULLET_SPEED{10};

Bullet::Bullet() : GameObject("resources/sprites/LaserGreen.png", {50.0f, 360.0f, 50.0f, 5.0f}, true)
{
    setSpeed(BULLET_SPEED);
    setActive(false);
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
}

void Bullet::collisions()
{
    if (getActive() && getX() > SCREEN_WIDTH)
    {
        toggleActive();
    }
}

void Bullet::draw()
{
    if (getActive())
    {
        DrawTexturePro(getTexture(), {0, 0, (float)getWidth(), (float)getHeight()}, {getX(), getY(), (float)getWidth(), (float)getHeight()}, {0.0f, 0.0f}, 0.0f, WHITE);
    }
}

void Bullet::destroy() {}