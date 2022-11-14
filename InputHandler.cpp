/*
    InputHandler.cpp
    20/10/2022

    Handle user input
    keyboard -- to do -- implent game controller
*/

#include "raylib.h"         // raylib library header
#include "InputHandler.hpp" // this class header
#include <iostream>         // working with strings

InputHandler *InputHandler::s_pInstance = 0; // single instance of the InputHandler

double timeSinceLastKeyPress = 0.0f; // counter - time since last key pressed
const float KEY_PRESS_DELAY = 0.2f;  // delay between key presses

/*
check is a key down
*/
bool InputHandler::isKeyDown(int key)
{
    return IsKeyDown(key); // return current key press
}

/*
check is a key down with a delay between presses
*/
bool InputHandler::isKeyDownDelay(int key)
{
    if (isKeyDown(key) && (GetTime() > (timeSinceLastKeyPress + KEY_PRESS_DELAY))) // a key is pressed and the time delay has passed
    {
        // std::cout << "Time InputHandler: " << GetTime() << " last key press " << timeSinceLastKeyPress << std::endl;
        timeSinceLastKeyPress = GetTime(); // reset the time delay to current time
        return IsKeyDown(key);             // return current key press (true if pressed | false if not pressed)
    }
    return false; // if enough time hasn't passed since the last key press return false
}

/*
if the select key / button / mouse left option is pressed
*/
bool InputHandler::select(bool delay) // delay paramater for slowing down time between presses
{
    if (delay) // if there is a delay
    {
        if (isKeyDownDelay(KEY_ENTER)) // if Enter is pressed, and there is enough of a delay since the last press
        {
            return true; // then enough time has passed since last key press
        }
    }
    else if (IsKeyDown(KEY_ENTER)) // if enter is pressed and there is no delay
    {
        return true; // return true
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseSelect) // if the left mouse button is prssed and the mouse can select an object (over an object)
    {
        std::cout << "input handler - mouse select" << std::endl;
        return true; // mouse has selected an object
    }
    return false; // no select button option matches return false
}

/*
left key, a key
*/
bool InputHandler::left(bool delay) // delay parameter leaves time between key presses
{
    if (delay) // if there is a deley between presses
    {
        if (isKeyDownDelay(KEY_A) || isKeyDownDelay(KEY_LEFT)) // if a or left arrow is pressed
        {
            return true; // then left button is pressed
        }
    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) // if no delay and left pressed
    {
        return true; // left key pressed
    }
    return false; // left key not pressed
}

/*
right key, d key
*/
bool InputHandler::right(bool delay) // delay parameter leaves time between key pressed
{
    if (delay) // if there is a delay between key presses
    {
        if (isKeyDownDelay(KEY_D) || isKeyDownDelay(KEY_RIGHT)) // if d or right is pressed
        {
            return true; // acknowledge key press
        }
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) // if no delay and D or right selected
    {
        return true; // acknowledge key press
    }
    return false; // otherise no key pressed, or not long enough of a delay
}
/*
up key, w key
*/
bool InputHandler::up(bool delay) // delay parameter leaves time between key pressed
{
    if (delay) // if there is a delay between key presses
    {
        if (isKeyDownDelay(KEY_W) || isKeyDownDelay(KEY_UP)) // if w or up key pressed
        {
            return true; // acknowledge key press
        }
    }
    else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) // if no delay and W or Up pressed
    {
        return true; // acknowledge key press
    }
    return false; // no key press, or not enough time since last key press
}
/*
down key, s key pressed
*/
bool InputHandler::down(bool delay) // set delay betwen button presses
{
    if (delay) // if there is a delay between button presses
    {
        if (isKeyDownDelay(KEY_S) || isKeyDownDelay(KEY_DOWN)) // if s or down pressed and there is a delay
        {
            return true; // acknowledge key press
        }
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) // if no delay and s or down pressed
    {
        return true; // acknowledge key press
    }
    return false; // if no key press, or not enough time since last key press
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