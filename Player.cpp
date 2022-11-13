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
#include "Particle.hpp"

const int PARTICLE_OFFSET_X = 75;
const int PARTICLE_OFFSET_Y = 10;

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
    setID(PLAYER);            // id to check collisions with other objects etc.
    setOffset({50, 25});      // collision offset
    setActive(true);          // object is active straight away
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
        debug("bullet" + std::to_string(i), DEBUG_MODE || DEBUG_PLAYER || DEBUG_BULLET); // only show if debugging players
    }

    red = LoadTexture("resources/particles/red.png");
    green = LoadTexture("resources/particles/green.png");
    blue = LoadTexture("resources/particles/blue.png");
    shimmer = LoadTexture("resources/particles/shimmer.png");

    for (int i = 0; i < PLAYER_PARTICLES; ++i)
    {
        particles[i] = new Particle({getPosition().x - PARTICLE_OFFSET_X, getPosition().y - PARTICLE_OFFSET_Y, 20, 15}, red, green, blue, shimmer);
    }
}

void Player::move()
{

    // Player flashes if collision with obstacle / enemy
    if (getCollision() && !isFlashing())
    {
        setCollision(false); // cancel collision flag
        setFlashing(true);   // set player flashing
    }
    // else
    // {
    //     setCollision(false); // todo -- check this
    // }

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

    handleInput(); // handle input
    collisions();  // check collisions

    // set sub object positions (needs to be after collision checking as they still move when the game area edges are touched)
    m_healthBar->setPosition({getX() - 50, getY() + (getHeight() / 2)});

    for (GameObject *b : getSubObjects()) // move objects
    {
        if ((*b).getActive())
        {
            (*b).move();
        }
    }
}

void Player::collisions()
{
    // check collisions with game area
    if (getX() < getWidth())
    {
        setX(getWidth());
    }
    else if ((getX() + getWidth()) >= SCREEN_WIDTH)
    {
        setX(SCREEN_WIDTH - getWidth());
    }

    if ((getY() - getHeight()) < 40) // offset by 40 for top of game area
    {
        setY(getHeight() + 40);
    }
    else if ((getY() + getHeight()) > SCREEN_HEIGHT - 120) // offset by 120 for bottom of game area
    {
        setY(SCREEN_HEIGHT - getHeight() - 120);
    }

    setCollisionRect({getX(), getY(), 100, 47}); // update collision rect position (after movement checked or box drags behind player), after collisions() stops bounding box moving when edge touched
}

void Player::drawParticles()
{
    for (int i = 0; i < PLAYER_PARTICLES; ++i)
    {
        if (!particles[i]->getActive())
        {
            delete particles[i];
            particles[i] = new Particle({getPosition().x - PARTICLE_OFFSET_X, getPosition().y - PARTICLE_OFFSET_Y, 20, 15}, red, green, blue, shimmer);
        }
    }

    for (int i = 0; i < PLAYER_PARTICLES; ++i)
    {
        particles[i]->draw();
    }
}

void Player::draw()
{
    DrawCircleV(getPosition(), getHeight(), MAROON);                                                                                                                                          // todo -- remember why you were using this
    DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, {255, (unsigned char)m_flashColourValue, (unsigned char)m_flashColourValue, 255}); // render player texture
    drawCollisionRect(DEBUG_PLAYER);                                                                                                                                                          // Bounding box to check collisions
    drawParticles();                                                                                                                                                                          // draw particles for player engine
}

void Player::handleInput()
{
    // x-axis movement
    if (Input::Instance()->right()) // right key, button pressed
    {
        setX(getX() + getSpeed()); // move right
    }
    else if (Input::Instance()->left()) // left key, button pressed
    {
        setX(getX() - getSpeed()); // move left
    }

    // y-axis movement
    if (Input::Instance()->up()) // up key, button pressed
    {
        setY(getY() - getSpeed()); // move up
    }
    else if (Input::Instance()->down()) // down key, button pressed
    {
        setY(getY() + getSpeed()); // move down
    }

    if (m_laserFireCount <= LASER_FIRE_RATE) // Only count if needs to
        m_laserFireCount++;                  // increment laser count each frame

    // attack
    if (Input::Instance()->isKeyDown(KEY_SPACE))
    {
        debug("player fire", (DEBUG_MODE || DEBUG_PLAYER));

        for (GameObject *b : getSubObjects()) // spawn bullets
        {
            if (m_laserFireCount >= LASER_FIRE_RATE) // time to fire another bullet
                if (!(*b).getActive() && (*b).getID() == PLAYER_BULLET)
                {
                    PlaySound(m_fxFire); // play laser sound effect

                    (*b).setPosition(getPosition());
                    (*b).toggleActive();
                    m_laserFireCount = 0; // reset wait until next bullet

                    debug(std::string("bullet active: ") + std::to_string((*b).getActive()) + " x: " + std::to_string((*b).getX()) + " y: " + std::to_string((*b).getY()), DEBUG_PLAYER || DEBUG_BULLET);
                    break;
                }
        }
    }
}

void Player::destroy()
{
    UnloadSound(m_fxFire);          // unload fire effect
    for (GameObject *g : particles) // get all particles
    {
        g->destroy(); // destroy them
    }
}

void Player::setHealth(int health)
{
    GameObject::setHealth(health); // Set player health

    StatusBar *hb = static_cast<StatusBar *>(m_healthBar); // status bar cast from GameObject base class
    hb->setPercent((float)getHealth() / 100.0f);           // Set health status bar percentage
    debug("healthbar should update - percent: " + std::to_string(hb->getPercent()), DEBUG_PLAYER || DEBUG_STATUSBAR);
}
