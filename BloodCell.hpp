/*
    BloodCell.hpp
    Joe O'Regan
    03/10/2022

    BloodCell background object -- to do -- make obstacle
*/

#ifndef BLOOD_CELL_HPP
#define BLOOD_CELL_HPP

#include "GameObject.hpp"

const bool TEST_BLOODCELL = true;

class BloodCell : public GameObject
{
public:
    BloodCell();    // constructor
    ~BloodCell() {} // deconstructor

    void init() {}     // initialise objects
    void move();       // update objects
    void collisions(); // check object collisions (no need here)
    void draw();       // render objects
    void destroy() {}  // clear objects from memory

    void setRotateClockwise(bool clockwise)
    {
        rotateClockwise = clockwise;
    }

    float getDegrees()
    {
        return m_degrees;
    }
    void setDegrees(float degrees)
    {
        m_degrees = degrees;
    }
    float m_degrees;
    bool rotateClockwise = true;
};

#endif