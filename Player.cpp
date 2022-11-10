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
#include "StatusBar.hpp"

Player::Player() : GameObject({50.0f, 320.0f, 50.0f, 50.0f}, "sprites/Player1Ship", true)
{
    setSpeed(8.0f);
    setCollision(false);

    m_fxFire = LoadSound("resources/fx/laser1.wav");
    m_laserFireCount = 0;

    m_flashing = false;
    m_flashCount = 0;
    m_flashColourValue = 255; // start green and blue values at max, only red flashes
    m_flashDirection = 1;     // colour values change positive / minus to flash the player
    setID(PLAYER);
}

void Player::init()
{
    m_healthBar = new StatusBar({getX() - 50, getY() + (getHeight() / 2), 100.0f, 10.0f}, 1.0f); // offset position to center under player
    // objects.push_back(m_healthBar);                                                              // add to objects list
    addSubObject(m_healthBar);

    m_laserFireCount = 0;
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        addSubObject(new Bullet());
        // if (DEBUG_MODE)
        // {
        //     std::cout << "bullet " << i << " added";
        // }
    }
}

void Player::move()
{

    // Player flashes if collision with obstacle / enemy
    if (getCollision() && !isFlashing())
    {
        setFlashing(true);
        // std::cout << "player has started flashing" << std::endl;
        setCollision(false);
    }
    else
    {
        setCollision(false);
    }

    if (isFlashing())
    {
        if (m_flashCount >= FLASH_TIMES) // when number of required of flashes reached
        {
            setFlashing(false); // stop flashing
            m_flashCount = 0;   // reset flashCount
            std::cout << "player has stopped flashing " << m_flashColourValue << std::endl;
        }
        else
        {
            m_flashColourValue += (FLASH_SPEED * m_flashDirection);

            if (m_flashColourValue >= 255 || m_flashColourValue <= 0) // change flash direction, white to red, red to white
            {
                m_flashDirection *= -1; // change direction of colour change at max and min values (255, 0)
                std::cout << "flash direction changed " << m_flashColourValue << std::endl;
            }

            if (m_flashColourValue >= 255)
            {
                m_flashColourValue = 255; // don't go beyond 255
                m_flashCount++;
                // std::cout << "player has flashed high " << m_flashCount << " times" << std::endl;
            }
            else if (m_flashColourValue <= 0)
            {
                m_flashColourValue = 0; // don't go below 0
                // std::cout << "player has flashed low " << m_flashCount << " times" << std::endl;
            }
        }
    }

    handleInput();
    m_healthBar->setPosition({getX() - 50, getY() + (getHeight() / 2)});

    for (GameObject *b : getSubObjects()) // move objects
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
    DrawCircleV(getPosition(), getHeight(), MAROON);
    // DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, WHITE);
    // DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, RED);
    DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, {255, (unsigned char)m_flashColourValue, (unsigned char)m_flashColourValue, 255});
    // Color(255, 255, 255);

    if (TEST_PLAYER)
    {
        // Bounding box to check collisions
        DrawRectangleLines(getX() - 50, getY() - 25, 100, 47, WHITE);
    }
}

void Player::destroy()
{
    UnloadSound(m_fxFire);
}

void Player::handleInput()
{
    if (InputHandler::Instance()->isKeyDown(KEY_RIGHT) ||
        InputHandler::Instance()->isKeyDown(KEY_D))
    {
        setX(getX() + getSpeed());
    }
    else if (InputHandler::Instance()->isKeyDown(KEY_LEFT) ||
             InputHandler::Instance()->isKeyDown(KEY_A))
    {
        setX(getX() - getSpeed());
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

    if (m_laserFireCount <= LASER_FIRE_RATE) // Only count if needs to
        m_laserFireCount++;                  // increment laser count each frame

    // attack
    if (InputHandler::Instance()->isKeyDown(KEY_SPACE))
    {
        // if (DEBUG_MODE)
        // {
        //     std::cout << "Player fire" << std::endl;
        // }

        for (GameObject *b : getSubObjects()) // spawn bullets
        {
            if (m_laserFireCount >= LASER_FIRE_RATE)
                if (!(*b).getActive() && (*b).getID() == BULLET)
                {
                    PlaySound(m_fxFire); // play laser sound effect

                    (*b).setX(getX());
                    (*b).setY(getY());
                    (*b).toggleActive();
                    m_laserFireCount = 0; // reset wait until next bullet

                    std::cout << "bullet active: " << (*b).getActive() << " x: " << (*b).getX() << " y: " << (*b).getY() << std::endl;
                    break;
                }
        }
    }
}

void Player::setHealth(int health)
{
    GameObject::setHealth(health);

    StatusBar *hb = static_cast<StatusBar *>(m_healthBar);
    hb->setPercent((float)getHealth() / 100.0f);
    // std::cout << "healthbar should update - percent: " << hb->getPercent() << std::endl;
}
