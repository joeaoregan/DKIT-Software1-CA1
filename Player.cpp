/*
    Player.cpp
    Joe O'Regan
    01/10/2022

    Player spaceship game object
*/

#include "Player.hpp"       // this class header file
#include "Bullet.hpp"       // player weapon sub object
#include <iostream>         // debug text using std::cout
#include "InputHandler.hpp" // handle user input for player ship
#include "StatusBar.hpp"    // player health bar sub object
#include "Particle.hpp"     // particles for player engine

const int PARTICLE_OFFSET_X = 75; // offset where the particle rect is drawn behind the player ship
const int PARTICLE_OFFSET_Y = 10; // offset where the particle rect is drawn behind the player ship and a bit lower

/*
Player constructor
*/
Player::Player() : GameObject({50.0f, 320.0f, 50.0f, 50.0f}, "sprites/Player1Ship", true) // constructor uses base class constructor to initialise member variables
{
    setSpeed(8.0f);      // sets the speed to 8 pixels per frame
    setCollision(false); // no collision by default

    m_fxFire = LoadSound("resources/fx/laser1.wav"); // load effect to play when bullet fired
    m_laserFireCount = 0;                            // counter - time between lasers firing, when space bar held will fire at steady rates

    m_flashing = false;       // player is not flashing to start
    m_flashCount = 0;         // counter for time between flashes
    m_flashColourValue = 255; // start green and blue values at max, only red flashes
    m_flashDirection = 1;     // colour values change positive / minus to flash the player
    setID(PLAYER);            // id to check collisions with other objects etc.
    setOffset({50, 25});      // collision offset
    setActive(true);          // object is active straight away
}

/*
initialise player
*/
void Player::init()
{
    m_healthBar = new StatusBar({getX() - 50, getY() + (getHeight() / 2), 100.0f, 10.0f}, 1.0f); // offset position to center under player

    m_laserFireCount = 0;                 // counter - time betwen lasers firing
    for (int i = 0; i < NUM_BULLETS; i++) // for up to the number of bullets specified
    {
        addSubObject(new Bullet());                                                      // add a new bullet as a usb object
        debug("bullet" + std::to_string(i), DEBUG_MODE || DEBUG_PLAYER || DEBUG_BULLET); // only show if debugging players
    }

    red = LoadTexture("resources/particles/red.png");         // load red texture for random rgb particle
    green = LoadTexture("resources/particles/green.png");     // load green texture for random rgb particle
    blue = LoadTexture("resources/particles/blue.png");       // load blue texture for random rgb particle
    shimmer = LoadTexture("resources/particles/shimmer.png"); // load shimmer texture for flashing particle

    for (int i = 0; i < PLAYER_PARTICLES; ++i) // for the amount of particles specified
    {
        particles[i] = new Particle({getPosition().x - PARTICLE_OFFSET_X, getPosition().y - PARTICLE_OFFSET_Y, 20, 15}, red, green, blue, shimmer); // add a random rgb particle for the player engine
    }
}

/*
update player movement
*/
void Player::move()
{
    // Player flashes if collision with obstacle / enemy
    if (getCollision() && !isFlashing()) // if player has collided, and is not already flashing
    {
        setCollision(false); // cancel collision flag
        setFlashing(true);   // set player flashing
    }

    if (isFlashing()) // if the player is flashing -- do ship flashing animation stuff
    {
        if (m_flashCount >= FLASH_TIMES) // when number of required of flashes reached
        {
            setFlashing(false);                                                             // stop flashing
            m_flashCount = 0;                                                               // reset flashCount
            std::cout << "player has stopped flashing " << m_flashColourValue << std::endl; // debug message
        }
        else // if still flashing
        {
            m_flashColourValue += (FLASH_SPEED * m_flashDirection); // update the flash colour value in the direction the colour value is moving

            if (m_flashColourValue >= 255 || m_flashColourValue <= 0) // change flash direction, white to red, red to white
            {
                m_flashDirection *= -1;                                                     // change direction of colour change at max and min values (255, 0)
                std::cout << "flash direction changed " << m_flashColourValue << std::endl; // debug text
            }

            if (m_flashColourValue >= 255) // if the flash colour value is > than 255 (or fully red)
            {
                m_flashColourValue = 255; // don't go beyond 255
                m_flashCount++;           // the number of complete flashes increases
                // std::cout << "player has flashed high " << m_flashCount << " times" << std::endl;
            }
            else if (m_flashColourValue <= 0) // if the flash colour value is the lowest it can be or lower than it should be
            {
                m_flashColourValue = 0; // don't go below 0
                // std::cout << "player has flashed low " << m_flashCount << " times" << std::endl;
            }
        }
    }

    handleInput(); // handle input -- todo -- call separately in state management
    collisions();  // check collisions -- todo -- call separately in state management

    // set sub object positions (needs to be after collision checking as they still move when the game area edges are touched)
    m_healthBar->setPosition({getX() - 50, getY() + (getHeight() / 2)}); // set the health status bar to follow player movement
    m_healthBar->move();                                                 // update the health status bar position

    for (GameObject *b : getSubObjects()) // update sub objects
    {
        if ((*b).getActive()) // if the object is active
        {
            (*b).move(); // update it
        }
    }
}

/*
player collisions
*/
void Player::collisions()
{
    // check collisions with game area
    if (getX() < PARTICLE_OFFSET_X) // if the player is less than the particle offset
    {
        setX(PARTICLE_OFFSET_X); // set the x value to the players particle offset -- keeps particles displayed on screen
    }
    else if ((getX() + getWidth()) >= SCREEN_WIDTH) // if the player is at the right edge of the screen (x is left side, so need to add width to get player rectangle right side)
    {
        setX(SCREEN_WIDTH - getWidth()); // set the player inside the screen bounds
    }

    if ((getY() - getHeight()) < GAME_AREA_TOP) // offset by 40 for top of game area (value in constants header)
    {
        setY(getHeight() + GAME_AREA_TOP); // keep player ship inside top of game area
    }
    else if ((getY() + getHeight()) > GAME_AREA_BOTTOM) // offset by 120 for bottom of game area (value in constants header)
    {
        setY(GAME_AREA_BOTTOM - getHeight()); // keep player ship inside bottom of game area
    }

    setCollisionRect({getX(), getY(), 100, 47}); // update collision rect position (after movement checked or box drags behind player), after collisions() stops bounding box moving when edge touched
}

/*
render particles emitted by player engine
*/
void Player::drawParticles()
{
    for (int i = 0; i < PLAYER_PARTICLES; ++i) // for the amount of particles specified in player header file
    {
        if (!particles[i]->getActive()) // if the particle is not active
        {
            delete particles[i];                                                                                                                        // delete the particle
            particles[i] = new Particle({getPosition().x - PARTICLE_OFFSET_X, getPosition().y - PARTICLE_OFFSET_Y, 20, 15}, red, green, blue, shimmer); // create a new random rgb particle
        }
        particles[i]->draw(); // render the particle
    }
}

/*
render player and particles
*/
void Player::draw()
{
    DrawCircleV(getPosition(), getHeight(), MAROON);                                                                                                                                          // todo -- remember why you were using this
    DrawTexturePro(getTexture(), {0, 0, 100, 47}, {getX() - 50, getY() - 25, 100, 47}, {0.0f, 0.0f}, 0.0f, {255, (unsigned char)m_flashColourValue, (unsigned char)m_flashColourValue, 255}); // render player texture
    drawCollisionRect(DEBUG_PLAYER);                                                                                                                                                          // Bounding box to check collisions
    drawParticles();                                                                                                                                                                          // draw random particles for player engine
    m_healthBar->draw();                                                                                                                                                                      // draw health status bar
}

/*
handle player user input
*/
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
    if (Input::Instance()->isKeyDown(KEY_SPACE)) // if fire button (space) pressed
    {
        debug("player fire", (DEBUG_MODE || DEBUG_PLAYER)); // debug message - player bullet firing

        for (GameObject *b : getSubObjects()) // spawn bullets
        {
            if (m_laserFireCount >= LASER_FIRE_RATE)                    // time to fire another bullet
                if (!(*b).getActive() && (*b).getID() == PLAYER_BULLET) // if an inactive object is found on the list, and the object is a bullet
                {
                    PlaySound(m_fxFire);             // play laser sound effect
                    (*b).setPosition(getPosition()); // set starting position of bullet as player position
                    (*b).toggleActive();             // set the bullet active
                    m_laserFireCount = 0;            // reset wait until next bullet

                    debug(std::string("bullet active: ") + std::to_string((*b).getActive()) + " x: " + std::to_string((*b).getX()) + " y: " + std::to_string((*b).getY()), DEBUG_PLAYER || DEBUG_BULLET); // debug bullet spawn point
                    break;                                                                                                                                                                                // finished when 1 bullet fired
                }
        }
    }
}

/*
destroy player
*/
void Player::destroy()
{
    UnloadSound(m_fxFire);          // unload fire effect
    for (GameObject *g : particles) // get all particles
    {
        g->destroy(); // destroy them
    }
}

/*
set player health and update health status bar
*/
void Player::setHealth(int health)
{
    GameObject::setHealth(health); // Set player health

    StatusBar *hb = static_cast<StatusBar *>(m_healthBar);                                                            // status bar cast from GameObject base class -- todo find tidier way of doing this without cast
    hb->setPercent((float)getHealth() / 100.0f);                                                                      // Set health status bar percentage
    debug("healthbar should update - percent: " + std::to_string(hb->getPercent()), DEBUG_PLAYER || DEBUG_STATUSBAR); // debug healthbar - check updating
}
