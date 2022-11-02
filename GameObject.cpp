/*
    GameObject.cpp
    Joe O'Regan
    01/10/2022

    Base class for game objects, such as player, background, etc
*/

#include "GameObject.hpp"

GameObject::GameObject() : m_collision(false)
{
}

GameObject::GameObject(Vector2 coordinates)
{
    m_position = coordinates;
}

GameObject::GameObject(std::string src, Rectangle rect, bool collidable) : GameObject({rect.x, rect.y})
{
    m_width = rect.width;
    m_height = rect.height;
    m_collidable = collidable;
    m_sprite = LoadTexture(("resources/" + src + ".png").c_str());
    m_currentFrame = 0;            // current frame of sprite animation
    m_totalFrames = 1;             // number of frames for animation
    m_isAnimationFinished = false; // animation finished
    m_canDestroy = false;          // object can be removed from memory
    m_isAnimationLoop = false;     // does the animation loop
    m_health = 100;                // health for object
}

GameObject::~GameObject() {}

void GameObject::init() {}
void GameObject::move() {}
void GameObject::collisions() {}
void GameObject::draw() {}

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