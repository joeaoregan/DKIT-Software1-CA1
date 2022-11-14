/*
    GameObject.cpp
    Joe O'Regan
    01/10/2022

    Base class for game objects, such as player, background, etc
*/

#include "GameObject.hpp" // game object header file
#include <iostream>       // std::string for passing in the name of the texture to load to the constructor

GameObject::GameObject() : m_id{GAME_OBJECT}, m_collision(false), m_currentFrame{0}, m_totalFrames{1}, m_isAnimationFinished{false}, m_isAnimationLoop{false}, m_health{100} // constructor and default values
{
    m_canDestroy = false;                   // object can be deleted
    m_collisionRectPositionOffset = {0, 0}; // offset for collision rect, default none
}

GameObject::GameObject(Rectangle rect, std::string src, bool collidable, int id) : GameObject() // constructor calls no args constructor
{
    m_rect = rect;          // x, y, width, height
    m_collisionRect = rect; // rectangle used for collisions ...edited for funny shapes etc.

    m_collidable = collidable; // some objects don't need to check for collisions
    if (src != "")
        m_sprite = LoadTexture(("resources/" + src + ".png").c_str()); // load the object texture
    m_id = id;                                                         // identify object for checking collisions etc.
}

/*
    what to do when the object is cleared from the games
*/
void GameObject::destroy()
{
    UnloadTexture(m_sprite); // unload the texture
}

/*
    cycle through animation frames until the animation finishes or begins looping again
*/
void GameObject::incrementFrame()
{
    m_currentFrame++;                    // increment the current animation frame
    if (m_currentFrame >= m_totalFrames) // when the last frame is reached
    {
        m_currentFrame = 0;     // reset the current animation frame
        if (!m_isAnimationLoop) // if the animation doesn't loop
        {
            m_isAnimationFinished = true; // set the animation as finished
        }
    }
}

/*
    debug messages - instead of including iostream and having to comment / uncomment them
*/
void GameObject::debug(std::string msg, bool debug)
{
    if (DEBUG_ALL || DEBUG_MESSAGE || debug) // if debugging all items, just messages, or the parameters passed in
    {
        std::cout << msg << std::endl; // display message
    }
}