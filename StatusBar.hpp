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
    StatusBar(Rectangle rect);
    StatusBar(Rectangle rect, float percent);
    StatusBar(Rectangle rect, Colour bg, Colour fg, Colour o);
    ~StatusBar();

    void init();
    void move();
    void collisions();
    void draw();
    void destroy();

    Rectangle bgRect, fgRect;

    float getPercent() { return m_percent; }
    void setPercent(float percent) { m_percent = percent; }

    void setForegroundColour(Colour c) { m_colourFG = c; }
    void setBackgroundColour(Colour c) { m_colourBG = c; }
    void setOutlineColour(Colour c) { m_colourOutline = c; }

private:
    float m_percent;

    Colour m_colourBG;
    Colour m_colourFG;
    Colour m_colourOutline;
};
#endif