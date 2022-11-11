/*
    Particle.hpp
    Joe O'Regan
    11/11/2022

    Add particles to player ship
*/

#include "GameObject.hpp"
#include <iostream>

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

class Particle : public GameObject
{
public:
    Particle(Rectangle rect, Texture2D &red, Texture2D &green, Texture2D &blue, Texture2D &shimmer); // Constructor: Initialize position and animation
    ~Particle()
    {
        // std::cout << "particle destroyed" << std::endl;
    }

    void init() {}       // initialise textures
    void move();         // update frame
    void collisions() {} // not needed
    void draw();         // render the particle
    void destroy();      // clear the textures

private:
    int mFrame; // Current frame of animation
    Texture2D *m_texture;
    Texture2D m_shimmer;
};

#endif