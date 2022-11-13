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

Explosion::Explosion(Vector2 position) : GameObject({position.x, position.y, 128.0f, 128.0f}, "ExplosionBlood", true)
{
    setTotalFrames(NUM_FRAMES);                         // number of animation frames
    setID(EXPLOSION);                                   // id is explosion - todo add more later
    setOffset({getWidth() / 2.0f, getHeight() / 2.0f}); // set offset for collision
    setCollisionRect((*getRect()));                     // init collision rect, offsetting it
    setActive(true);
}

Explosion::~Explosion()
{
    std::cout << "Explosion destroyed" << std::endl;
}

void Explosion::move()
{
    if (getActive()) // if it's not active skip all this
    {
        const float deltaTime(GetFrameTime()); // get the delta time
        runningTime += deltaTime;              // time since last frame change
        if (runningTime > updateTime)          // what to do each animation frame
        {
            runningTime = 0.0f;        // reset frame running time
            incrementFrame();          // increment frame count
            if (isAnimationFinished()) // what to do when animation is finished
            {
                setPosition({-getWidth(), 0}); // move off screen -- todo - delete
                setActive(false);              // object is no longer active
                setCanDestroy(true);           // object can be destroyed
            }
        }
    }
}

void Explosion::draw()
{
    if (getActive()) // if the Explosion is active
    {
        DrawTextureRec(getTexture(), {(getFrame() * 128.0f), 0.0f, 128.0f, 128.0f}, {getX() - (getWidth() / 2), getY() - (getHeight() / 2)}, WHITE); // render texture
        drawCollisionRect(DEBUG_EXPLOSION);                                                                                                          // show the rectangle used to determine collisions
    }
}

void Explosion::destroy()
{
    GameObject::destroy(); // call destroy in base class
}