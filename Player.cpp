/*
    Joe O'Regan
    01/10/2022
*/

#include "Player.hpp"
#include "Bullet.hpp"
#include <iostream>

Player::Player()
{
    setSpeed(8.0f);
    setPosition({50.0f, 320.0f});
    setHeight(50);
    setWidth(50);
    fxFire = LoadSound("resources/fx/laser1.wav");
    setSprite("resources/sprites/Player1Ship.png");
}

Player::~Player()
{
}

void Player::init()
{
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        bullets.push_back(new Bullet());
        if (DEBUG_MODE)
        {
            std::cout << "bullet " << i << " added";
        }
    }
}

void Player::move()
{
    // move
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        setX(getX() + getSpeed());
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        setX(getX() - getSpeed());
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        setY(getY() - getSpeed());
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        setY(getY() + getSpeed());

    // attack
    if (IsKeyPressed(KEY_SPACE))
    {
        if (DEBUG_MODE)
        {
            std::cout << "Player fire" << std::endl;
        }

        for (GameObject *b : bullets) // spawn bullets
        {
            if (!(*b).getActive())
            {
                PlaySound(fxFire);

                (*b).setX(getX());
                (*b).setY(getY());
                (*b).toggleActive();

                std::cout << "bullet active" << std::endl;
                break;
            }
        }
    }

    for (GameObject *b : bullets) // move bullets
    {
        if ((*b).getActive())
        {
            (*b).move();
        }
    }
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

    // bullets
    for (GameObject *b : bullets)
    {
        if ((*b).getActive())
        {
            (*b).collisions();
        }
    }
}

void Player::draw()
{
    DrawCircleV(getPosition(), getHeight(), MAROON);
    DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, WHITE);

    // bullets
    for (GameObject *b : bullets)
    {
        (*b).draw();
    }
}

void Player::destroy()
{
    UnloadSound(fxFire);
}