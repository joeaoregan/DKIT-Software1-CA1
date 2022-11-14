/*
    Particle.cpp
    Joe O'Regan
    11/11/2022

    Particle game object
    Add particles to player ship
    Credit: LazyFoo tutorial
*/

#include "Particle.hpp" // this class header file
#include <iostream>     // debug text

/*
particle constructor
*/
Particle::Particle(Rectangle rect, Texture2D &red, Texture2D &green, Texture2D &blue, Texture2D &shimmer) // texture rectangle, 1 shimmer texture, and randomly selecting colour texture
{
    setX(rect.x + (rand() % (int)rect.width));  // random x coordinate in rectangle area
    setY(rect.y + (rand() % (int)rect.height)); // random y coordinate in rectangle area
    mFrame = rand() % 5;                        // random frame 0 to 4
    m_shimmer = shimmer;                        // shimmer texture always usable

    switch (rand() % 3) // with a random number of 0 to 2
    {
    case 0:              // if the random number is 0
        setTexture(red); // use the red texture, sets m_sprite in game object base class
        break;
    case 1:                // if the random number is 1
        setTexture(green); // use the green texture, sets m_sprite in game object base class
        break;
    case 2:               // if the random number is 2
        setTexture(blue); // use the blue texture, sets m_sprite in game object base class
        break;
    }
}

/*
update particles
*/
void Particle::move()
{
    mFrame++;        // increment animation frame
    if (mFrame > 10) // if the animation frame is greater than 10
    {
        setActive(false); // set the particle as inactive
    }
}

/*
render particles
*/
void Particle::draw()
{
    if (getActive())
    {
        DrawTexture(getTexture(), getPosition().x, getPosition().y, WHITE); // render the randomly selected colour particle
        if (mFrame % 2 == 0)                                                // ever 2nd frame
        {
            DrawTexture(m_shimmer, getPosition().x, getPosition().y, WHITE); // render the constant shimmer particle flashing over coloured particle
        }
    }
}

/*
destroy particles
*/
void Particle::destroy()
{
    GameObject::destroy();    // call base class destroy function clears rgb texture
    UnloadTexture(m_shimmer); // unload shimmer texture
}