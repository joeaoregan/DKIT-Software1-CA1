/*
    Bullet.cpp
    Joe O'Regan
    02/10/2022

    Player weapon
*/

#include "Bullet.hpp"

Bullet::Bullet()
{
    setX(50);
    setY(360);
    setSpeed(5);
    setWidth(50);
    setHeight(5);
    setSprite("resources/sprites/LaserGreen.png");
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