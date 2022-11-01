/*
    Background.cpp
    Joe O'Regan
    02/10/2022

    Scrolling Background
    Renders behind other game objects
*/

#include "Background.hpp"

const int SCROLL_SPEED = 2; // speed to scroll the background across the screen

Background::Background() : GameObject("Background720", {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}, false)
{
    bg2X = getX() + SCREEN_WIDTH;
}

Background::~Background()
{
}

void Background::init()
{
    // sort constructor stuff, maybe some goes here
}

void Background::move()
{
    setX(getX() - SCROLL_SPEED);
    bg2X -= SCROLL_SPEED;

    if (getX() <= -(SCREEN_WIDTH))
    {
        setX(SCREEN_WIDTH);
    }
    if (bg2X <= -(SCREEN_WIDTH))
    {
        bg2X = SCREEN_WIDTH;
    }
}

void Background::collisions()
{
}

void Background::draw()
{
    DrawTexture(getTexture(), getX(), 0, WHITE);
    DrawTexture(getTexture(), bg2X, 0, WHITE);
}

void Background::destroy() {}