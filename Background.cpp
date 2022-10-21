/*
    Background.cpp
    Joe O'Regan
    02/10/2022

    Scrolling Background
    Renders behind other game objects
*/

#include "Background.hpp"

const int SCROLL_SPEED = 2; // speed to scroll the background across the screen

Background::Background()
{
    Image image = LoadImage("resources/Background720.png"); // Image to use as background
    setTexture(image);                                      // create texture from image
    UnloadImage(image);                                     // unload the image now the texture is created

    setPosition({0.0f, 0.0f}); // starting position is the origin x,y = 0,0
    setHeight(SCREEN_HEIGHT);  // match height of screen
    setWidth(SCREEN_WIDTH);    // match width of screen
    setX(0);                   //
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