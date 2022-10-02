/*
    Joe O'Regan
    01/10/2022
*/

#include "Player.hpp"

Player::Player()
{
    setSpeed(8.0f);
    setPosition({50.0f, 320.0f});
    setHeight(50);
    setWidth(50);
}

Player::~Player()
{
}

void Player::move()
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        setX(getX() + getSpeed());
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        setX(getX() - getSpeed());
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        setY(getY() - getSpeed());
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        setY(getY() + getSpeed());
}

void Player::collisions()
{
    if (getX() < getWidth())
    {
        setX(getWidth());
    }
    else if ((getX() + getWidth()) >= SCREEN_WIDTH)
    {
        setX(SCREEN_WIDTH - getWidth());
    }

    if ((getY() - getHeight()) < 0)
    {
        setY(getHeight());
    }
    else if ((getY() + getHeight()) > SCREEN_HEIGHT)
    {
        setY(SCREEN_HEIGHT - getHeight());
    }
}

void Player::draw()
{
    DrawCircleV(getPosition(), getHeight(), MAROON);
}