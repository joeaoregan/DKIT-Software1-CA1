/*
    BloodCell.cpp
    Joe O'Regan
    03/10/2022

    BloodCell background object -- to do -- make obstacle
*/

#include "BloodCell.hpp"
#include <iostream>

int MOVEMENT = (GetRandomValue(0, 20) * 5) + 350;
;
const int SPACE_BETWEEN_CELLS = 150;
int dy = GetRandomValue(0, 250);
bool movingUp = (GetRandomValue(0, 10) % 2 == 0) ? true : false;
float dRotate = 0.0f;
int upDownSpeed = GetRandomValue(10, 15);

BloodCell::BloodCell()
{
    setX(SCREEN_WIDTH + (SPACE_BETWEEN_CELLS * GetRandomValue(0, 10)));
    setY(350);
    int randomYPosition = (GetRandomValue(0, 7) * 55) + 90;
    // setY((GetRandomValue(1, 10) * getHeight()) + 20);
    // setY(90);// top of screen
    // setY(495); // bottom of screen
    // setY((GetRandomValue(0, 7) * getHeight()) + 90);
    // setY((getHeight() * GetRandomValue(0, 7)) + 90);
    setY(randomYPosition);
    setWidth(100);
    setHeight(55);
    setSpeed((GetRandomValue(1, 5) / 5.0f) + 0.6f);
    setSprite("resources/sprites/BloodCell.png");
    setRotateClockwise((GetRandomValue(0, 10) % 2 == 0) ? true : false);
    dRotate = (GetRandomValue(1, 10) / 10 * 0.5f) + 0.5f;
    setDegrees(GetRandomValue(0, 360));
}

BloodCell::~BloodCell() {}
void BloodCell::init() {}
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
}

void BloodCell::draw()
{
    // setY(getY() + (dy / upDownSpeed));

    DrawTexturePro(getTexture(), {0, 0, (float)getWidth(), (float)getHeight()},
                   {getX() + (getWidth() / 2), getY() + (getHeight() / 2), (float)getWidth(), (float)getHeight()},
                   {getWidth() / 2.0f, getHeight() / 2.0f}, ((rotateClockwise) ? getDegrees() : getDegrees() * -1), WHITE);

    if (TEST_BLOODCELL)
    {
        DrawRectangleLines(getX(), getY(), getWidth(), getHeight(), WHITE);
    }
}

void BloodCell::destroy() {}