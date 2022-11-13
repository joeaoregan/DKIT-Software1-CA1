/*
    BloodCell.hpp
    Joe O'Regan
    03/10/2022

    BloodCell background object -- to do -- make obstacle
*/

#ifndef BLOOD_CELL_HPP
#define BLOOD_CELL_HPP

#include "GameObject.hpp" // GameObject base class header file

const bool DEBUG_BLOODCELL = true; // debug the blood cell class

class BloodCell : public GameObject // BloodCell is a child of GameObject
{
public:
    BloodCell();    // constructor
    ~BloodCell() {} // deconstructor

    void init() {}     // initialise objects
    void move();       // update objects
    void collisions(); // check object collisions (no need here)
    void draw();       // render objects
    void destroy() {}  // clear objects from memory

    Vector2 getOrigin() { return {getWidth() / 2.0f, getHeight() / 2.0f}; } // origin point to rotate on (center of rect)

    void updateCollisionRects(); // update collision rect size and position depending on rotation of blood cell

private:
    void setRotateClockwise(bool clockwise) { rotateClockwise = clockwise; } // which direction to rotate the blood cell
    float getDegrees() { return m_degrees; }                                 // get the degrees to rotate by
    void setDegrees(float degrees) { m_degrees = degrees; }                  // set the degrees to rotate by
    float m_degrees;                                                         // degrees to rotate by
    bool rotateClockwise = true;                                             // direction to rotate (clockwise if true)
    Rectangle cRect1, cRect2, cRect3;                                        // Dynamic collision rect states
};

#endif