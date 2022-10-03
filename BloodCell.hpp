/*
    Joe O'Regan
    03/10/2022
*/

#ifndef BLOOD_CELL_HPP
#define BLOOD_CELL_HPP

#include "GameObject.hpp"

class BloodCell : public GameObject
{
public:
    BloodCell();
    ~BloodCell();

    void init();
    void move();
    void collisions();
    void draw();
    void destroy();

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