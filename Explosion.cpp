/*
    Explosion.cpp
    Joe O'Regan
    01/11/2022

    Explosion game object
*/
#include "Explosion.hpp"
#include <iostream>

const float updateTime(1.0f / 20); // update every 1/20th of a frame
const int NUM_FRAMES{16};          // number of animation frames -- todo not every animation will have 16 frames

/*
    Explosion constructor
*/
Explosion::Explosion(Vector2 position) : GameObject({position.x, position.y, 128.0f, 128.0f}, "ExplosionBlood", true) // Game object base class constructor used to initialise object
{
    setTotalFrames(NUM_FRAMES);                         // number of animation frames
    setID(EXPLOSION);                                   // id is explosion - todo add more later
    setOffset({getWidth() / 2.0f, getHeight() / 2.0f}); // set offset for collision
    setCollisionRect((*getRect()));                     // init collision rect, offsetting it
    setActive(true);                                    // explosion active straight away -- todo - change to use same amount of blood explosions as blood cells, and resuse as not being deleted
}

/*
    Explosion destructor
*/
Explosion::~Explosion()
{
    debug("explosion destroyed", DEBUG_EXPLOSION); // show when debugging
}

/*
    update explosion animation
*/
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

/*
    render Explosion
*/
void Explosion::draw()
{
    if (getActive()) // if the Explosion is active
    {
        DrawTextureRec(getTexture(), {(getFrame() * 128.0f), 0.0f, 128.0f, 128.0f}, {getX() - (getWidth() / 2), getY() - (getHeight() / 2)}, WHITE); // render texture
        drawCollisionRect(DEBUG_EXPLOSION);                                                                                                          // show the rectangle used to determine collisions
    }
}

/*
    destroy explosion object -- todo check if this does anything between levels, 1st implement 1 level
*/
void Explosion::destroy()
{
    GameObject::destroy(); // call destroy in base class
}