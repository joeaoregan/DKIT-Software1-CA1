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

Explosion::Explosion(Vector2 position) : GameObject({position.x, position.y, 128.0f, 128.0f}, "ExplosionBlood")
{
    setTotalFrames(NUM_FRAMES);                         // number of animation frames
    setID(EXPLOSION);                                   // id is explosion - todo add more later
    setOffset({getWidth() / 2.0f, getHeight() / 2.0f}); // set offset for collision
    setCollisionRect((*getRect()));                     // init collision rect, offsetting it
}

Explosion::~Explosion()
{
    std::cout << "Explosion destroyed" << std::endl;
}

void Explosion::move()
{
    const float deltaTime(GetFrameTime());
    runningTime += deltaTime;
    if (runningTime > updateTime)
    {
        runningTime = 0.0f;
        incrementFrame();
        if (isAnimationFinished())
        {
            setActive(false);
            setCanDestroy(true);
        }
    }
}

void Explosion::draw()
{
    if (getActive())
    {
        DrawTextureRec(getTexture(), {(getFrame() * 128.0f), 0.0f, 128.0f, 128.0f}, {getX() - (getWidth() / 2), getY() - (getHeight() / 2)}, WHITE);
        drawCollisionRect(DEBUG_EXPLOSION);
    }
}

void Explosion::destroy()
{
    GameObject::destroy(); // call destroy in base class
}