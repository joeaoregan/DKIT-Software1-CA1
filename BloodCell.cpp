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

BloodCell::BloodCell() : GameObject({0.0f, 0.0f, 100.0f, 55.0f}, "sprites/BloodCell", true)
{
    setX(SCREEN_WIDTH + (SPACE_BETWEEN_CELLS * GetRandomValue(0, 10)));
    int randomYPosition = (GetRandomValue(0, 7) * 55) + 90;
    // setY((GetRandomValue(1, 10) * getHeight()) + 20);
    // setY((GetRandomValue(0, 7) * getHeight()) + 90);
    // setY((getHeight() * GetRandomValue(0, 7)) + 90);
    setY(randomYPosition);

    setSpeed((GetRandomValue(1, 5) / 5.0f) + 0.6f);
    setRotateClockwise((GetRandomValue(0, 10) % 2 == 0) ? true : false);
    dRotate = (GetRandomValue(1, 10) / 10 * 0.5f) + 0.5f;
    setDegrees(GetRandomValue(0, 360));
    setDamage(5); // amount of damage to inflict on the player
    setID(BLOOD_CELL);
    updateCollisionRects();
}

void BloodCell::updateCollisionRects()
{
    if (getActive())
    {
        cRect1 = {(*getRect()).x - originOffsetX, (*getRect()).y - originOffsetY, width, height};
        cRect2 = {(*getRect()).x - originOffsetX + rect2Offset, (*getRect()).y - originOffsetY - rect2Offset, height, width};
        cRect3 = {(*getRect()).x - originOffsetX + rect3Offset, (*getRect()).y - originOffsetY - rect3Offset, width - rect2Offset, height + rect2Offset};
    }
}

void BloodCell::move()
{
    setX(getX() - getSpeed());
    setDegrees(getDegrees() + dRotate);

    if (getDegrees() >= 360)
        setDegrees(0);

    if (movingUp)
        dy++;
    else
        dy--;

    if (dy > MOVEMENT)
        movingUp = false;
    else if (dy <= 0)
        movingUp = true;

    // setY(getY() + (dy / upDownSpeed));

    collisions();
}

void BloodCell::collisions()
{
    if ((getX() < -getWidth()) || getCollision()) // if moved off screen, or collided with
    {
        setX(SCREEN_WIDTH + (SPACE_BETWEEN_CELLS * GetRandomValue(0, 10)));
        // std::cout << "bloodcell off screen" << std::endl;
        setCollision(false);
    }

    updateCollisionRects();

    // dynamically change the collision rect
    if (getDegrees() < 30 || getDegrees() >= 330 || (getDegrees() >= 150 && getDegrees() < 210))
    {
        setCollisionRect(cRect1); // wide rectangle
    }
    else if ((getDegrees() >= 60 && getDegrees() < 120) || (getDegrees() >= 240 && getDegrees() < 300))
    {
        setCollisionRect(cRect2); // rectangle rotated 90
    }
    else
    {
        setCollisionRect(cRect3); // in between 0 and 90 degree rotation, more like a square
    }
}

void BloodCell::draw()
{
    DrawTexturePro(getTexture(), {0, 0, getWidth(), getHeight()}, (*getRect()), getOrigin(), ((rotateClockwise) ? getDegrees() : getDegrees() * -1), WHITE);
    drawCollisionRect(DEBUG_BLOODCELL);
}
