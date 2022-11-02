/*
    StatusBar.hpp
    Joe O'Regan
    01/11/2022
*/

#ifndef STATUS_BAR_HPP
#define STATUS_BAR_HPP

#include "GameObject.hpp"

class StatusBar : public GameObject // StatusBar inherits directly from the GameObject base class
{
public:
    StatusBar(Rectangle rect, float percent);
    ~StatusBar();

    void init();
    void move();
    void collisions();
    void draw();
    void destroy();

    Rectangle bgRect, fgRect;

    float getPercent() { return m_percent; }
    void setPercent(float percent) { m_percent = percent; }

    float m_percent;
};
#endif