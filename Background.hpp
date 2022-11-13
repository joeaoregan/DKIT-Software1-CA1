/*
    Background.hpp
    Joe O'Regan
    02/10/2022

    Scrolling Background
    Renders behind other game objects
*/
#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "GameObject.hpp"

class Background : public GameObject
{
public:
    Background(Vector2 position = {0.0f, 0.0f}); // constructor - default position argurment
    ~Background() {}                             // deconstructor

    void init() {}       // initialise the object
    void move();         // update the object
    void collisions() {} // check collisions with other objects
    void draw();         // render the object
    void destroy() {}    // remove the object from memory

    int bg2X; // starting point for 2nd part of scrolling background
};

#endif