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

void InputHandler::update()
{
    // to do
    // std::cout << "Time InputHandler: " << GetTime() << " last key press " << timeSinceLastKeyPress << std::endl;
}

void InputHandler::close()
{
    // to do
}

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
