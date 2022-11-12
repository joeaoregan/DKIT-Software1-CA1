/*
    InputHandler.cpp
    20/10/2022

    Handle user input
    keyboard -- to do -- implent game controller
*/

#include "raylib.h"
#include "InputHandler.hpp"
#include <iostream>

InputHandler *InputHandler::s_pInstance = 0;

double timeSinceLastKeyPress = 0.0f;
const float KEY_PRESS_DELAY = 0.2f;

bool InputHandler::isKeyDown(int key)
{
    return IsKeyDown(key); // return current key press
}

bool InputHandler::isKeyDownDelay(int key)
{
    if (isKeyDown(key) && (GetTime() > (timeSinceLastKeyPress + KEY_PRESS_DELAY)))
    {
        // std::cout << "Time InputHandler: " << GetTime() << " last key press " << timeSinceLastKeyPress << std::endl;
        timeSinceLastKeyPress = GetTime();
        return IsKeyDown(key); // return current key press
    }
    return false;
}

bool InputHandler::select(bool delay)
{
    if (delay)
    {
        if (isKeyDownDelay(KEY_ENTER))
        {
            return true;
        }
    }
    else if (IsKeyDown(KEY_ENTER))
    {
        return true;
    }
    return false;
}

bool InputHandler::left(bool delay)
{
    if (delay)
    {
        if (isKeyDownDelay(KEY_A) || isKeyDownDelay(KEY_LEFT))
        {
            return true;
        }
    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        return true;
    }
    return false;
}
bool InputHandler::right(bool delay)
{
    if (delay)
    {
        if (isKeyDownDelay(KEY_D) || isKeyDownDelay(KEY_RIGHT))
        {
            return true;
        }
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        return true;
    }
    return false;
}
bool InputHandler::up(bool delay)
{
    if (delay)
    {
        if (isKeyDownDelay(KEY_W) || isKeyDownDelay(KEY_UP))
        {
            return true;
        }
    }
    else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        return true;
    }
    return false;
}
bool InputHandler::down(bool delay)
{
    if (delay)
    {
        if (isKeyDownDelay(KEY_S) || isKeyDownDelay(KEY_DOWN))
        {
            return true;
        }
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        return true;
    }
    return false;
}

/*
    Check is the mouse pointer over the rectangle
*/
bool InputHandler::mouseOver(Rectangle *a, Vector2 cursor)
{
    // Calculate the sides of button
    float rectLeft = (*a).x;                 // left side
    float rectRight = (*a).x + (*a).width;   // right side
    float rectTop = (*a).y;                  // top
    float rectBottom = (*a).y + (*a).height; // bottom

    int x = (cursor).x; // cursor x
    int y = (cursor).y; // cursor y

    // check if mouse x/y outside of object rect
    if (y < rectTop)
        return false; // cursor over button
    else if (y > rectBottom)
        return false; // cursor under button
    else if (x < rectLeft)
        return false; // cursor to left of button
    else if (x > rectRight)
        return false; // cursor to right of button

    return true; // If cursor x/y not outside the rect -> Hovering!
}