/*
    Bullet.cpp
    Joe O'Regan
    02/10/2022

    Player weapon
*/

#include "Bullet.hpp" // Bullet header file

const int BULLET_SPEED{10}; // bullet speed

Bullet::Bullet() : GameObject({-50.0f, 360.0f, 50.0f, 5.0f}, "sprites/LaserGreen", true, PLAYER_BULLET) // Bullet uses game object base class constructor to initialise
{
    setSpeed(BULLET_SPEED); // speed to move bullet at
    setActive(false);       // not active until player fires
}

void Bullet::move()
{
    if (getActive()) // if the bullet is active
    {
        setX(getX() + getSpeed()); // update the x position
    }

    collisions(); // what to do if collisions with other objects
}

void Bullet::collisions()
{
    if (getCollision() || getX() >= SCREEN_WIDTH) // if the bullet has collided with another object, or gone off screen to the right
    {
        debug("bullet collision", DEBUG_BULLET || DEBUG_COLLISIONS); // message displayed when testing bullets or collisions
        setActive(false);                                            // the bullet is no longer active
        setPosition({-getWidth(), 0});                               // move off screen
        setCollision(false);                                         // reset collisions
    }
    if (getActive()) // if the bullet is active
    {
        setCollisionRect((*getRect())); // update collision rect position (move with bullet)
    }
}

void Bullet::draw()
{
    if (getActive()) // If the bullet is active, then draw
    {
        DrawTexturePro(getTexture(), {0, 0, getWidth(), getHeight()}, (*getRect()), {0.0f, 0.0f}, 0.0f, WHITE); // draw the bullet texture
        drawCollisionRect(DEBUG_BULLET);                                                                        // draws the collision rect for testing
    }
}
