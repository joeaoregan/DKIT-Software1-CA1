/*
    GameObject.cpp
    Joe O'Regan
    01/10/2022

    Base class for game objects, such as player, background, etc
*/

#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject() : m_id{GAME_OBJECT}, m_collision(false), m_currentFrame{0}, m_totalFrames{1}, m_isAnimationFinished{false}, m_isAnimationLoop{false}, m_health{100}
{
    m_canDestroy = false; // object can be deleted
    offset = {0, 0};      // offset for collision rect
}

GameObject::GameObject(Rectangle rect, std::string src, bool collidable, int id) : GameObject()
{
    m_rect = rect;          // x, y, width, height
    m_collisionRect = rect; // rectangle used for collisions ...edited for funny shapes etc.

    m_collidable = collidable;                                     // some objects don't need to check for collisions
    m_sprite = LoadTexture(("resources/" + src + ".png").c_str()); // load the object texture
    m_id = id;                                                     // identify object for checking collisions etc.
}

void GameObject::destroy()
{
    UnloadTexture(m_sprite); // unload the texture
}

void GameObject::incrementFrame()
{
    m_currentFrame++; // increment the current animation frame
    if (m_currentFrame >= m_totalFrames)
    {
        m_currentFrame = 0;     // reset the current animation frame
        if (!m_isAnimationLoop) // if the animation doesn't loop
        {
            m_isAnimationFinished = true; // set the animation as finished
        }
    }
}

void GameObject::debug(std::string msg, bool debug)
{
    if (DEBUG_ALL || DEBUG_MESSAGE || debug)
    {
        std::cout << msg << std::endl; // display message
    }
}