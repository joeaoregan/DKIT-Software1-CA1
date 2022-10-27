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

GameObject::GameObject(const char *textureSRC, Rectangle rect, bool collidable) : GameObject({rect.x, rect.y})
{
    m_width = rect.width;
    m_height = rect.height;
    m_collidable = collidable;
    m_sprite = LoadTexture(textureSRC);
}

GameObject::~GameObject() {}

void GameObject::init() {}
void GameObject::move() {}
void GameObject::collisions() {}
void GameObject::draw() {}
void GameObject::destroy() {}