/*
    Background.cpp
    Joe O'Regan
    02/10/2022

    Scrolling Background
    Renders behind other game objects
*/

#include "Background.hpp" // background header file

const int SCROLL_SPEED = 2; // speed to scroll the background across the screen

// Background bg2 = new Background({SCREEN_WIDTH, 0.0f});

Background::Background(Vector2 pos) : GameObject({pos.x, pos.y, SCREEN_WIDTH, SCREEN_HEIGHT}, "Background720") // background uses GameObject base class to initialise
{
    bg2X = getX() + SCREEN_WIDTH; // x coordinate of background 2
}

/*
    update background object
*/
void Background::move()
{
    setX(getX() - SCROLL_SPEED); // set speed for 1st background image
    bg2X -= SCROLL_SPEED;        // set speed for 2nd background image

    if (getX() <= -(SCREEN_WIDTH)) // if 1st background has moved fully off screen to the left
    {
        setX(SCREEN_WIDTH); // move it back to to fully off screen to right
    }
    if (bg2X <= -(SCREEN_WIDTH)) // if 2nd background has moved fully off screen to the left
    {
        bg2X = SCREEN_WIDTH; // move it back to to fully off screen to right
    }
}

/*
    render background images
*/
void Background::draw()
{
    DrawTexture(getTexture(), getX(), 0, WHITE); // render background texture
    DrawTexture(getTexture(), bg2X, 0, WHITE);   // render 2nd background texture
}
