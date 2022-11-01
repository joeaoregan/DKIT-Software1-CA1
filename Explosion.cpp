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

Explosion::Explosion(Vector2 position) : GameObject("ExplosionBlood", {position.x, position.y, 128.0f, 128.0f}, false)
{
    setTotalFrames(NUM_FRAMES);
}

Explosion::~Explosion()
{
    std::cout << "Explosion destroyed" << std::endl;
}

void Explosion::init() {}

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

void Explosion::collisions() {}

void Explosion::draw()
{
    if (getActive())
        DrawTextureRec(getTexture(), {(getFrame() * 128.0f), 0.0f, 128.0f, 128.0f}, {getX() - (getWidth() / 4), getY() - (getHeight() / 4)}, WHITE);
}

void Explosion::destroy()
{
    GameObject::destroy(); // call destroy in base class
}