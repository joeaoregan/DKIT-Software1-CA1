/*
    GameObject.cpp
    Joe O'Regan
    01/10/2022

    Base class for game objects, such as player, background, etc
*/

#include "GameObject.hpp"

GameObject::GameObject() : m_id{GAME_OBJECT}, m_collision(false), m_currentFrame{0}, m_totalFrames{1}, m_isAnimationFinished{false}, m_isAnimationLoop{false}, m_health{100}
{
    m_canDestroy = false;
}

GameObject::GameObject(Rectangle rect, std::string src, bool collidable) : GameObject()
{
    m_position = {rect.x, rect.y};
    m_width = rect.width;
    m_height = rect.height;
    m_collidable = collidable;
    m_sprite = LoadTexture(("resources/" + src + ".png").c_str());
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