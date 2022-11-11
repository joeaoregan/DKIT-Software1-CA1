/*
    Particle.cpp
    Joe O'Regan
    11/11/2022

    Particle game object
    Add particles to player ship
*/

#include "Particle.hpp"
#include <iostream>

Particle::Particle(Rectangle rect, Texture2D &red, Texture2D &green, Texture2D &blue, Texture2D &shimmer)
{
    setX(rect.x + (rand() % (int)rect.width));
    setY(rect.y + (rand() % (int)rect.height));
    mFrame = rand() % 5;

    m_shimmer = shimmer;

    switch (rand() % 3)
    {
    case 0:
        // setTexture(red);
        m_texture = &red;
        break;
    case 1:
        // setTexture(green);
        m_texture = &green;
        break;
    case 2:
        // setTexture(blue);
        m_texture = &blue;
        break;
    }
}

void Particle::move()
{
    mFrame++;
    if (mFrame > 10)
    {
        setActive(false);
    }
}

void Particle::draw()
{
    DrawTexture(*m_texture, getPosition().x, getPosition().y, WHITE);
    if (mFrame % 2 == 0)
    {
        DrawTexture(m_shimmer, getPosition().x, getPosition().y, WHITE);
    }
}

void Particle::destroy()
{
    GameObject::destroy();
    UnloadTexture(m_shimmer);
}