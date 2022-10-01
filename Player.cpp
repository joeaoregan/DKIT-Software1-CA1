/*
    Joe O'Regan
    01/10/2022
*/

#include "Player.h"

Player::Player()
{
    setSpeed(5.0f);
    setPosition({50.0f, 320.0f});
    setHeight(50);
    setWidth(50);
}

Player::~Player()
{
}

void Player::move()
{
    if (IsKeyDown(KEY_RIGHT))
        setX(getX() + getSpeed());
    else if (IsKeyDown(KEY_LEFT))
        setX(getX() - getSpeed());
    if (IsKeyDown(KEY_UP))
        setY(getY() - getSpeed());
    else if (IsKeyDown(KEY_DOWN))
        setY(getY() + getSpeed());
}

void Player::collisions()
{
    if (getX() < getWidth())
    {
        setX(getWidth());
    }
}