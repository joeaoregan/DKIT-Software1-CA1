/*
    Explosion.cpp
    Joe O'Regan
    01/11/2022

    Explosion game object
*/
#include "Explosion.hpp"
#include <iostream>

const float updateTime(1.0f / 20);
const int NUM_FRAMES{16};

Explosion::Explosion() : GameObject("resources/ExplosionBlood.png", {50.0f, 320.0f, 128.0f, 128.0f}, false)
{
    frame = 0;
}

Explosion::~Explosion()
{
}

void Explosion::init() {}

void Explosion::move()
{
    const float deltaTime(GetFrameTime());
    runningTime += deltaTime;
    if (runningTime > updateTime)
    {
        runningTime = 0.0f;
        frame++;
        if (frame >= NUM_FRAMES)
        {
            setActive(false);
            canDestroy = true;
        }
    }
}

void Explosion::collisions() {}

void Explosion::draw()
{
    if (getActive())
        DrawTextureRec(getTexture(), {(frame * 128.0f), 0.0f, 128.0f, 128.0f}, {getX() - (getWidth() / 4), getY() - (getHeight() / 4)}, WHITE);
}

void Explosion::destroy()
{
    UnloadTexture(getTexture());
    // std: :cout << "explosion destroyed" << std::endl;
}