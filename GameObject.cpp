/*
    Joe O'Regan
    01/10/2022
*/

#include "GameObject.hpp"

GameObject::GameObject()
{
}
GameObject::GameObject(Vector2 coordinates)
{
    m_position = coordinates;
}

GameObject::~GameObject() {}

void GameObject::init() {}
void GameObject::move() {}
void GameObject::collisions() {}
void GameObject::draw() {}
void GameObject::destroy() {}