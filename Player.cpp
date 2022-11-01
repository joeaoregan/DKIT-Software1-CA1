/*
    Player.cpp
    Joe O'Regan
    01/10/2022

    Player spaceship game object
*/

#include "Player.hpp"
#include "Bullet.hpp"
#include <iostream>
#include "InputHandler.hpp"

const int LASER_FIRE_RATE = 20; // time until next laser blast

Player::Player() : GameObject("resources/sprites/Player1Ship.png", {50.0f, 320.0f, 50.0f, 50.0f}, true)
{
    setSpeed(8.0f);
    fxFire = LoadSound("resources/fx/laser1.wav");
    setCollision(false);
    laserFireCount = 0;
}

Player::~Player()
{
}

void Player::init()
{
    laserFireCount = 0;
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        bullets.push_back(new Bullet());
        // if (DEBUG_MODE)
        // {
        //     std::cout << "bullet " << i << " added";
        // }
    }
}

void Player::move()
{
    // Player flashes if collision with obstacle / enemy
    if (getCollision())
    {
        flash += (flashSpeed * direction);

        if (flash > 254 || flash < 1) // change flash direction, white to red, red to white
        {
            direction *= -1; // change direction at the top
            if (flash > 255)
            {
                flash = 255; // don't go beyond 255
                flashCount++;
            }
            else if (flash < 0)
                flash = 0; // don't go below 0
        }

        if (flashCount >= flashTimes)
        {
            setCollision(false);
            flashCount = 0; // reset flashCount
        }
    }

    handleInput();

    for (GameObject *b : bullets) // move objects
    {
        if ((*b).getActive())
        {
            (*b).move();
        }
    }

    collisions();
}

void Player::collisions()
{
    // test collision
    // if (getX() > 200 && !getCollision()) // if the player moves over 200 px, and the player is not already after colliding with an object
    // {
    //     setCollision(true); // the player is after colliding
    // }

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
    GameObject::draw();
    DrawCircleV(getPosition(), getHeight(), MAROON);
    // DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, WHITE);
    // DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, RED);
    DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, {255, (unsigned char)flash, (unsigned char)flash, 255});
    // Color(255, 255, 255);

    if (TEST_PLAYER)
    {
        // Bounding box to check collisions
        DrawRectangleLines(getX() - 50, getY() - 25, 100, 47, WHITE);
    }
}

void Player::destroy()
{
    UnloadSound(fxFire);
}

void Player::handleInput()
{
    if (InputHandler::Instance()->isKeyDown(KEY_RIGHT) ||
        InputHandler::Instance()->isKeyDown(KEY_D))
    {
        setX(getX() + getSpeed());
        // std::cout << "Pressed Left" << std::endl;
    }
    else if (InputHandler::Instance()->isKeyDown(KEY_LEFT) ||
             InputHandler::Instance()->isKeyDown(KEY_A))
    {
        setX(getX() - getSpeed());
        // std::cout << "Pressed Right" << std::endl;
    }

    if (InputHandler::Instance()->isKeyDown(KEY_UP) ||
        InputHandler::Instance()->isKeyDown(KEY_W))
    {
        setY(getY() - getSpeed());
    }
    else if (InputHandler::Instance()->isKeyDown(KEY_DOWN) ||
             InputHandler::Instance()->isKeyDown(KEY_S))
    {

        setY(getY() + getSpeed());
    }

    if (laserFireCount <= LASER_FIRE_RATE) // Only count if needs to
        laserFireCount++;                  // increment laser count each frame

    // attack
    if (InputHandler::Instance()->isKeyDown(KEY_SPACE))
    {
        // if (DEBUG_MODE)
        // {
        //     std::cout << "Player fire" << std::endl;
        // }

        for (GameObject *b : bullets) // spawn bullets
        {
            if (laserFireCount >= LASER_FIRE_RATE)
                if (!(*b).getActive())
                {
                    PlaySound(fxFire);

                    (*b).setX(getX());
                    (*b).setY(getY());
                    (*b).toggleActive();
                    laserFireCount = 0; // reset wait until next bullet

                    std::cout << "bullet active: " << (*b).getActive() << " x: " << (*b).getX() << " y: " << (*b).getY() << std::endl;
                    break;
                }
        }
    }
}