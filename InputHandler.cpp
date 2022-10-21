/*
    InputHandler.cpp
    20/10/2022

    Handle user input
    keyboard -- to do -- implent game controller
*/

#include "raylib.h"
#include "InputHandler.hpp"

InputHandler *InputHandler::s_pInstance = 0;

void InputHandler::update()
{
    // to do
}

void InputHandler::close()
{
    // to do
}

bool InputHandler::isKeyDown(int key)
{
    return IsKeyDown(key); // return current key press
}
