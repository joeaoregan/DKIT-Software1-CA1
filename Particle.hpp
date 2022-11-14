/*
    Particle.hpp
    Joe O'Regan
    11/11/2022

    Add particles to player ship
*/

#include "GameObject.hpp" // parent game object class header file

#ifndef PARTICLE_HPP // if particle class not defined already, checking it's not used twice
#define PARTICLE_HPP // ok to define this class

class Particle : public GameObject // Particle is a direct child of GameObject class
{
public:                                                                                              // public members accessible from anywhere
    Particle(Rectangle rect, Texture2D &red, Texture2D &green, Texture2D &blue, Texture2D &shimmer); // Constructor: Initialize position and animation
    ~Particle()
    {
        // std::cout << "particle destroyed" << std::endl; // todo -- implement destructors
    }

    void init() {}       // initialise textures
    void move();         // update frame
    void collisions() {} // not needed
    void draw();         // render the particle
    void destroy();      // clear the textures

private:                 // private members only accessible from this clas
    int mFrame;          // Current frame of animation
    Texture2D m_shimmer; // shimmer texture for particle
};                       // end of class

#endif // end of definition