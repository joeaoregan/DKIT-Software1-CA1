/*
    BloodCell.cpp
    Joe O'Regan
    03/10/2022

    BloodCell background object -- to do -- make obstacle
*/

#include "BloodCell.hpp"
#include <iostream>

// dynamic bounding box
const int width = 100;
const int height = 50;
const int originOffsetX = width / 2;
const int originOffsetY = height / 2;
const int rect2Offset = (width - height) / 2;
const int rect3Offset = rect2Offset / 2;

int MOVEMENT = (GetRandomValue(0, 20) * 5) + 350;

const int SPACE_BETWEEN_CELLS = 150;
int dy = GetRandomValue(0, 250);
bool movingUp = (GetRandomValue(0, 10) % 2 == 0) ? true : false;
float dRotate = 0.0f;
int upDownSpeed = GetRandomValue(10, 15);

/*
    Blood Cell object constructor
*/
BloodCell::BloodCell() : GameObject({0.0f, 0.0f, 100.0f, 55.0f}, "sprites/BloodCell", true) // BloodCell uses GameObject parent class constructor to initialise
{
    setX(SCREEN_WIDTH + (SPACE_BETWEEN_CELLS * GetRandomValue(0, 10)));  // random x starting position off screen to the right
    int randomYPosition = (GetRandomValue(0, 7) * 55) + 90;              // calculate random y starting position starting at 90 pixels, then every 55 pixels up to 7 times
    setY(randomYPosition);                                               // set random y position
    setSpeed((GetRandomValue(1, 5) / 5.0f) + 0.6f);                      // speed to move
    setRotateClockwise((GetRandomValue(0, 10) % 2 == 0) ? true : false); // direction to rotate
    dRotate = (GetRandomValue(1, 10) / 10 * 0.5f) + 0.5f;                // amount to rotate each frame
    setDegrees(GetRandomValue(0, 360));                                  // start the blood cell rotating at a random degree
    setDamage(5);                                                        // amount of damage to inflict on the player
    setID(BLOOD_CELL);                                                   // ID to check collisions etc and distinguish from other objects
    updateCollisionRects();                                              // use to initialise the collision rectangle
    setActive(true);                                                     // The blood cell is active once created
}

/*
    update the 3 different sized collision rects
*/
void BloodCell::updateCollisionRects()
{
    if (getActive()) // if the blood cell is active update the rectangle used for collisions
    {
        cRect1 = {(*getRect()).x - originOffsetX, (*getRect()).y - originOffsetY, width, height};                                                         // blood cell starting rectangle
        cRect2 = {(*getRect()).x - originOffsetX + rect2Offset, (*getRect()).y - originOffsetY - rect2Offset, height, width};                             // in between angle
        cRect3 = {(*getRect()).x - originOffsetX + rect3Offset, (*getRect()).y - originOffsetY - rect3Offset, width - rect2Offset, height + rect2Offset}; // upright, basically rotated 90 degrees
    }
}

/*
    update the BloodCell movement and other actions
*/
void BloodCell::move()
{
    setX(getX() - getSpeed());          // move left to right
    setDegrees(getDegrees() + dRotate); // update the rotation

    if (getDegrees() >= 360)
        setDegrees(0); // reset degrees to 0 once it hits 360

    if (movingUp) // if its moving up dy increases -- todo check am I adding or subtracting this because it should decrease for up
        dy++;     // difference to increase y position
    else
        dy--; // if moving down decrease y value

    if (dy > MOVEMENT)    // if the blood cell has reached the peak of its upward movement start moving down again
        movingUp = false; // commence moving down
    else if (dy <= 0)     // if the blood cell has reached the peak of its downward movement, need to start moving up
        movingUp = true;  // keep moving up

    // setY(getY() + (dy / upDownSpeed)); // todo - try and remember what I was attempting here

    collisions(); // check collisions -- todo make this a funcion in gameobject, as most objects have collisions anyway
}

/*
    what to do when a BloodCell collides with another object
*/
void BloodCell::collisions()
{

    if ((getX() < -getWidth()) || getCollision()) // if moved off screen, or collided with
    {
        // std::cout << "bloodcell off screen" << std::endl;
        setX(SCREEN_WIDTH + (SPACE_BETWEEN_CELLS * GetRandomValue(0, 10))); // move a random distance to the right of the screen to start all over again
        setCollision(false);                                                // reset the collision flag
    }

    // dynamically change the collision rect
    if (getDegrees() < 30 || getDegrees() >= 330 || (getDegrees() >= 150 && getDegrees() < 210))
    {
        setCollisionRect(cRect1); // wide rectangle
    }
    else if ((getDegrees() >= 60 && getDegrees() < 120) || (getDegrees() >= 240 && getDegrees() < 300)) // if degrees is between 60 and 120, or 240 and 300 use rotated 90 degrees bounding box
    {
        setCollisionRect(cRect2); // rectangle rotated 90
    }
    else // if it's in any other position, use the square type
    {
        setCollisionRect(cRect3); // in between 0 and 90 degree rotation, more like a square
    }

    updateCollisionRects(); // Dynamically update the collision rectangle shape as the blood cell rotates
}

/*
    render the blood cell
*/
void BloodCell::draw()
{
    DrawTexturePro(getTexture(), {0, 0, getWidth(), getHeight()}, (*getRect()), getOrigin(), ((rotateClockwise) ? getDegrees() : getDegrees() * -1), WHITE);
    drawCollisionRect(DEBUG_BLOODCELL); // if debugging render the collisions rectangle bounding box
}
